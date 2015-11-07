require 'set'
require 'fileutils'

def mkdir (dir_name)
    FileUtils.mkdir_p(dir_name) unless Dir.exist?(dir_name)
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
        res += if File.file?(child_path) && /.*\.[ch]/.match(child_path)
                   [child_path]
               else
                   list_files(child_path + '/*')
               end
    end
    res
end

def get_project_root (dumpfile)
    res = Set.new
    File.open(dumpfile).each { |line|
        res.add(line.split[1]) if /DW_AT_comp_dir/.match(line)
    }
    raise '[ERROR] ' + dumpfile + ' size is not 1' unless res.size == 1
    # Give back the ONLY element in set
    res.to_a[0]
end

def mk_html_files(old_root, new_root)
    list_content(old_root).each { |child_path|
        if File.file?(child_path) && /.*\.[ch]/.match(child_path)
            mkdir(new_root + '/' + File.expand_path('..', child_path))
            File.open(new_root + child_path + '.html', 'w+'){ |html_f|
                File.open(child_path, 'r'){|orig_f|
                    html_f.write('<HTML>')
                    html_f.write('<BODY>')
                    html_f.write('<xmp>')
                    orig_f.each { |line|
                        html_f.write(line )
                    }
                    html_f.write('</xmp>')
                    html_f.write('</BODY>')
                    html_f.write('</HTML>')
                }
            }
        else
            mk_html_files(child_path + '/*', new_root)
        end
    }
end

def main
    mkdir('./HTML')
    p_root = get_project_root('./test/dump1.txt')
    mk_html_files(p_root, './HTML')
end

if __FILE__ == $0
    main
end
