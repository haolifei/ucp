protoc = Builder(action='thirdparty/bin/protoc --proto_path=proto  --cpp_out=proto/ $SOURCE') 
env_gen = Environment(BUILDERS={'Protoc':protoc})

env_gen.Protoc(['proto/master.pb.h','proto/master.pb.cc'], 'proto/master.proto')


env = Environment(
        CPPPATH = ['.'] ,
        LIBS = ['thread'],
        LIBPATH = [''],
        CCFLAGS = '-g2 -Wall -Werror -Wno-unused-but-set-variable')


env.Program('test', ['master/hello.cc', 'proto/master.pb.cc'])
