protoc = Builder(action='thirdparty/bin/protoc --proto_path=./proto  --cpp_out=proto/ $SOURCE') 
env_gen = Environment(BUILDERS={'Protoc':protoc})

env_gen.Protoc(['proto/master.pb.h','proto/master.pb.cc'], 'proto/master.proto')

env = Environment(
        CPPPATH = ['.', 'worker', 'thirdparty/boost_1_57_0/', './thirdparty/include', './thirdparty/rapidjson/include'],
        LIBS = ['glog', 'gflags', 'tcmalloc', 'unwind', 'ins_sdk', 'sofa-pbrpc', 'snappy', 'protobuf', 'pthread', 'z', 'rt', 'boost_filesystem', 'gtest', 'common', 'tera', 'libzookeeper_mt'],
        LIBPATH = ['./thirdparty/lib', './thirdparty/boost_1_57_0/stage/lib'],
        CCFLAGS = '-g2 -Wall -Werror -Wno-unused-but-set-variable',
        LINKFLAGS = '-Wl,-rpath-link ./thirdparty/boost_1_57_0/stage/lib')

env.Program('master.exe', Glob('master/*.cc') + ['proto/master.pb.cc'])
env.Program('worker.exe', Glob('worker/*/*.cc') + Glob('worker/*.cc') + ['proto/master.pb.cc'])

