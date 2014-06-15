assert 'Process.uid' do
  assert_kind_of Fixnum, Process.uid
end

assert 'Process.gid' do
  assert_kind_of Fixnum, Process.gid
end

assert 'Process.euid' do
  assert_kind_of Fixnum, Process.euid
end

assert 'Process.egid' do
  assert_kind_of Fixnum, Process.egid
end
