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

def take_tag_val (tag_name, str)
    m = /#{tag_name}<{1,2}([^>]*)>{1,2}/.match(str)
    m[1].to_s if m
end

def get_project_root (dumpfile)
    res = Set.new
    File.open(dumpfile).each { |line|
        tag_val = take_tag_val('DW_AT_comp_dir', line)
        res.add(tag_val) if tag_val 
    }
    raise "[ERROR] " + dumpfile + " size is not 1" unless res.size == 1
    # Give back the ONLY element in set
    res.to_a[0]
end

def get_file_lines (filename)
    File.foreach(filename) {}
    $.
end

def mk_html_files(old_root, new_root)
    list_content(old_root).each { |child_path|
        if File.file?(child_path) && is_interesting_filetype(child_path) 
            mkdir(new_root + '/' + File.expand_path('..', child_path))
            File.open(new_root + child_path + '.html', 'w+'){ |html_f|
                File.open(child_path, 'r'){|orig_f|
                    html_f.write("<!DOCTYPE HTML>\n")
                    html_f.write("<BODY>\n")
                    html_f.write("<code>\n")
                    File.foreach(orig_f).with_index { |line, line_num|
                        line = (line_num + 1).to_s.ljust(get_file_lines(child_path).to_s.length, " ") + ' ' +  line
                        # order of these replacement matters
                        # amp should go first
                        line = line.gsub(/&/,'&amp;')
                        line = line.gsub(/ /, '&nbsp;')
                        line = line.gsub(/</,'&#60;')
                        line = line.gsub(/>/,'&gt;')
                        html_f.write( line + "<br>\n")
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

def mk_index_file (index_file_path, list_files)
    mkdir(File.expand_path('..', index_file_path))
    File.open(index_file_path, 'w+')  {|f|
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
        f.write('Created WD: ' +  Dir.getwd.to_s)
        f.write("</BODY>\n")
        f.write("</HTML>\n")
    }
end


def generate_dumpfile(binary_path)
    out_path = binary_path + '.dump'
    cmd = 'dwarfdump -di ' + '-O file=' + out_path + ' ' + binary_path
    %x(#{cmd})
    out_path
end


def main
    dumpfile_path = generate_dumpfile(ARGV[0].to_s)
    p_root = get_project_root(dumpfile_path)
    puts p_root
    mk_html_files(p_root, './HTML')
    mk_index_file('./HTML/index.html', list_files(p_root))
end

if __FILE__ == $0
    main
end
