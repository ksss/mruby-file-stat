mruby_version = ENV["MRUBY_VERSION"] || 'master'
mruby_dir = "mruby-#{mruby_version}"

file mruby_dir do
  sh "git clone --depth=1 --branch #{mruby_version} git://github.com/mruby/mruby.git"
  sh "mv mruby #{mruby_dir}"
end

file "#{mruby_dir}/ci_build_config.rb" => [mruby_dir, ".ci_build_config.rb"] do
  sh "cp #{File.expand_path(".ci_build_config.rb")} #{mruby_dir}/ci_build_config.rb"
end

desc "run test with mruby"
task :test => "#{mruby_dir}/ci_build_config.rb" do
  cd mruby_dir do
    sh "rake -E 'STDOUT.sync=true' test all MRUBY_CONFIG=ci_build_config.rb"
  end
end
