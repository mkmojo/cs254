require 'set'
require 'fileutils'

def mkdir (dir_name)
  FileUtils.mkdir_p(dir_name) unless Dir.exist?(dir_name)
end

def is_interesting_filetype (path)
  /.*\.([ch]|dump)/.match(path)
end

def list_content(path)
  if File.file?(path)
    nil
  else
    Dir.glob(path)
  end
end

def list_files (path)
  res = []
  list_content(path).each do |child_path|
    res += if File.file?(child_path) && is_interesting_filetype(child_path)
             [child_path]
           else
             list_files(child_path + '/*')
           end
  end
  res
end

def get_tag_val (tag_name, str)
  m = /#{tag_name}<{1,2}([^>]*)>{1,2}/.match(str)
  m[1].to_s if m
end

def get_project_root (dumpfile)
  res = Set.new
  File.open(dumpfile).each { |line|
    tag_val = get_tag_val('DW_AT_comp_dir', line)
    res.add(tag_val) if tag_val
  }
  raise '[ERROR] ' + dumpfile + ' size is not 1' unless res.size == 1
  # Give back the ONLY one element in set
  res.to_a[0]
end

def get_file_lines (filename)
  File.foreach(filename) {}
  $.
end

def generate_dumpfile(binary_path)
  out_path = binary_path + '.dump'
  cmd = 'dwarfdump -di ' + '-O file=' + out_path + ' ' + binary_path
  %x(#{cmd})
  out_path
end


class CompileUnit

  def initialize(name='', comp_dir='', lines='')
    @type = 'DW_TAG_compile_unit'
    @name = name
    @comp_dir = comp_dir
    @idents = []
    @lines = lines
  end

  def name
    @name
  end

  def comp_dir
    @comp_dir
  end

  def idents
    @idents
  end

  def add(ident)
    @idents.push(ident)
  end

  def get_ident_type(line)
    line.split[0].gsub(/[<>]/, ' ').split[2]
  end

  def to_s
    [@name, @comp_dir, ('idents.size: ' + @idents.size.to_s), @idents].join("\n")
  end

end

class Ident
  def initialize(type = '', scope=-1, name='', src_path='', line_num=-1, id='')
    @type = type
    @scope = scope
    @name = name
    @src_path = src_path
    @line_num = Integer(line_num, 16)
    @id = id
  end

  def type
    @type
  end

  def scope
    @scope
  end

  def name
    @name
  end

  def src_path
    @src_path
  end

  def line_num
    @line_num
  end

  def id
    @id
  end

  def to_s
    [@type, @scope.to_s, @name, @src_path, @line_num, @id].join(', ')
  end

  def Ident.get_abs_path(path, comp_dir)
    if path[0] == '/'
      path
    else
      comp_dir + '/' + path
    end
  end

end

def get_src_path(tag, line, comp_dir)
  if get_tag_val(tag, line)
    path = get_tag_val(tag, line).split[1]
    Ident.get_abs_path(path, comp_dir)
  else
    nil
  end
end

def build_compile_unit (lines)
  # lines is a list of line for identifiers
  cu = CompileUnit.new
  lines.each_with_index { |line, line_num|
    case cu.get_ident_type(line)
    when 'DW_TAG_compile_unit'
      cnt_name = get_tag_val('DW_AT_name', line)
      cnt_comp_dir = get_tag_val('DW_AT_comp_dir', line)
      cu = CompileUnit.new(cnt_name, cnt_comp_dir)
    else
      if (cnt_type = cu.get_ident_type(line))&&
        (cnt_scope = get_tag_val('', line.split[0]).to_i) &&
        (cnt_name = get_tag_val('DW_AT_name', line)) &&
        (cnt_src_path = get_src_path('DW_AT_decl_file', line, cu.comp_dir))&&
        (cnt_line_num = get_tag_val('DW_AT_decl_line', line)) &&
        (cnt_id = cu.name + '-' + line_num.to_s)
        cnt_ident = Ident.new(cnt_type, cnt_scope, cnt_name, cnt_src_path, cnt_line_num, cnt_id)
        #puts cnt_ident.to_s
        cu.add(cnt_ident)
      end
    end
  }
  cu
end

def build_compile_units(dumpfile)
  lines = File.readlines(dumpfile)
  $i=0
  cus = {} 
  cu_lines = []
  while $i < lines.size
    cnt_line = lines[$i]
    if cnt_line.size == 0
      next
    elsif cnt_line[0] == "\n" && cu_lines.size > 0
      cu = build_compile_unit(cu_lines)
      cus[[cu.comp_dir, cu.name].join('/')] = cu
      cu_lines = []
    elsif cnt_line[0] == '<'
      cu_lines.push(cnt_line)
    end
    $i = $i + 1
  end
  cus
end

def mk_index_file (index_file_path, list_files)
  mkdir(File.expand_path('..', index_file_path))
  File.open(index_file_path, 'w+') { |f|
    f.write("<!DOCTYPE HTML>\n")
    f.write("<BODY>\n")
    list_files.each { |file_name|
      url = '.' + file_name + '.html'
      f.write('<p>')
      f.write('<a href="' + url + '">' + file_name + '</a>')
      f.write("</p>\n")
    }
    # Make time stamp
    f.write('Created Time: ' + File.mtime(f).to_s + '<br>')
    # File location
    f.write('Created WD: ' + Dir.getwd.to_s)
    f.write("</BODY>\n")
    f.write("</HTML>\n")
  }
end

def get_line_with_num_from_html_page(html_file, line_num)
  File.readlines(html_file).detect{
    |line|
    line.start_with?(line_num.to_s)
  }
end

def mk_html_files(old_root, new_root)
  list_content(old_root).each { |child_path|
    if File.file?(child_path) && is_interesting_filetype(child_path)
      mkdir(new_root + '/' + File.expand_path('..', child_path))
      File.open(new_root + child_path + '.html', 'w+') { |html_f|
        n_child_path = get_file_lines(child_path)
        File.open(child_path, 'r') { |orig_f|
          html_f.write("<!DOCTYPE HTML>\n")
          html_f.write("<BODY>\n")
          html_f.write("<code>\n")
          File.foreach(orig_f).with_index { |line, line_num|
            line = (line_num + 1).to_s.ljust(n_child_path.to_s.length, " ") + ' ' + line
            # order of these replacement matters
            # amp should go first
            line = line.gsub(/&/, '&amp;')
            line = line.gsub(/ /, '&nbsp;')
            line = line.gsub(/</, '&#60;')
            line = line.gsub(/>/, '&gt;')
            html_f.write(line + "<br>\n")
          }
          html_f.write("</code>\n")
          html_f.write("</BODY>\n")
          html_f.write("</HTML>\n")
        }
      }
    else
      mk_html_files(child_path + '/*', new_root)
    end
  }
end

def add_global_ident_tag(src_file_path, line_num, line, cu)
  #print 'DEBUG: src_file_path: ',src_file_path ,' line_num: ' ,line_num, "\n"
  ident = cu.idents.detect{|i| i.src_path == src_file_path && i.line_num == line_num }
  if ident 
    line.gsub(/#{ident.name}/, '<a name = "' + ident.id + '">\0</a>')
  else
    line
  end
end

# TODO: use this function to generate HTML pages
def mk_html_pages(old_root, new_root, cus)
  list_content(old_root).each { |child_path|
    if File.file?(child_path) && is_interesting_filetype(child_path)
      #make sure parent dir exists
      mkdir(new_root + '/' + File.expand_path('..', child_path))
      File.open(new_root + child_path + '.html', 'w+') { |html_f|
        n_child_path = get_file_lines(child_path)
        File.open(child_path, 'r') { |orig_f|
          html_f.write("<!DOCTYPE HTML>\n")
          html_f.write("<BODY>\n")
          html_f.write("<code>\n")
          #start decorating each line in orig_f
          File.foreach(orig_f).with_index { |line, line_num|
            # order of these replacement matters
            # amp should go first
            line = line.gsub(/&/, '&#38;')
            line = line.gsub(/</, '&#60;')
            line = line.gsub(/>/, '&#62;')
            line = line.gsub(/ /, '&#160;')

            if (cu = cus[orig_f.path])
              #child_path is absolute path
              #print 'DEBUG: child_path is ', child_path, "\n"
              line = add_global_ident_tag(child_path, line_num + 1, line, cu)
            end


            line = (line_num + 1).to_s.ljust(n_child_path.to_s.length, " ") + ' ' + line
            html_f.write(line + "<br>\n")
          }
          html_f.write("</code>\n")
          html_f.write("</BODY>\n")
          html_f.write("</HTML>\n")
        }
      }
    else
      mk_html_pages(child_path + '/*', new_root, cus)
    end
  }
end


def main
  dumpfile_path = generate_dumpfile(ARGV[0].to_s)
  puts p_root = get_project_root(dumpfile_path)
  cus = build_compile_units(dumpfile_path)
  mk_html_pages(p_root, './HTML',cus)
  mk_index_file('./HTML/index.html', list_files(p_root))
  #print stuff out
  cus.values.each { |cu|
    puts cu.to_s
    puts
  }
end

if __FILE__ == $0
  main
end
