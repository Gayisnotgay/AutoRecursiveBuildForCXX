# ===============工程目录相关的定义=============== #
# 解释：PROJECT_ROOT_PATH是工程根目录，下面有code，script和build共3个子目录
# code: 顾名思义，存放你的XXX.cpp,XXX.h代码，可以有子目录
# script: 存放了Makefile模板文件，里面一共有4个Makefile文件：Makefile, Makefile_subdir, Makefile_utils, Makefile_final。
#   【注意】：前3个脚本是核心运行脚本，保证能够递归编译出所有的点O文件，别轻易修改。最后一个Makefile_final脚本可以根据自己的需求随意修改。
#         [!X]Makefile：make入口脚本（本文件），定义了编译器名称，编译选项，头文件搜索路径等，是递归编译的入口
#         [!X]Makefile_subdir：子目录编译的make脚本，由Makefile调用，不需要外部调用
#         [!X]Makefile_utils：定义了一些通用的代码块
#         [.OK]Makefile_final：对生成的目标文件进行打包，链接甚至生成可执行文件，可以根据自己需求随意修改

# build: 存放构建过程中输出的目标文件,按照code中的目录层次存放输出的目标文件
# build/final: 存放可执行文件和库文件
# ===============工程目录相关的定义=============== #
export PROJECT_ROOT_PATH := $(realpath ..)
export PROJECT_BUILD_ROOT_PATH := $(realpath .)
export PROJECT_CODE_ROOT_PATH := $(PROJECT_ROOT_PATH)/code
export PROJECT_MAKEFILES_PATH := $(PROJECT_ROOT_PATH)/script
include $(PROJECT_MAKEFILES_PATH)/Makefile_utils
# 预期应该生成的目标文件列表
export PROJECT_EXPECTED_OBJECTPATH_LIST := $(subst $(PROJECT_CODE_ROOT_PATH),$(PROJECT_BUILD_ROOT_PATH),$(subst .cpp,.o,$(call GetAllFilePathsInDir,$(PROJECT_CODE_ROOT_PATH),cpp)))

# PROJECT_DIR_INCLUDE_LIST定义了代码的头文件搜索目录
# 【注意】：
# 1.0 为了图省事，作者将code目录下面所有子目录的路径全部加了进来，而优秀的C++代码应该有一个清晰的头文件目录划分，不同模块的源文件不应该跨模块包含其他模块的头文件，否则就说明代码的模块划分不合理。
#     所以PROJECT_DIR_INCLUDE_LIST列表可以根据自己的实际情况来修改
# 2.0 当需要包含第三方库的头文件时，可以如下在下面添加一行
#     export PROJECT_DIR_INCLUDE_LIST := $(PROJECT_DIR_INCLUDE_LIST) /XXX/XXXXX/ThirdpatyInclude/
export PROJECT_DIR_INCLUDE_LIST := $(call GetAllSubDirPaths,$(PROJECT_CODE_ROOT_PATH))


# CC定义编译器名称，前提是环境上已经装好了编译器。CC名称不要修改，否则会影响make自动规则推导。
export CC := g++
# CPPFLAGS为编译选项，编译标志等（头文件包含路径也加到了这里）。CPPFLAGS名称不要修改，否则会影响make自动规则推导。
export CPPFLAGS := -g -fPIC $(addprefix -I ,$(PROJECT_DIR_INCLUDE_LIST))
# SHARED_LIBRARY_SUFFIX为动态库的后缀，因为在linux和windows下的动态库后缀不一样
export SHARED_LIBRARY_SUFFIX := $(if $(findstring lib%.dll,$(.LIBPATTERNS)),dll,so)

CUR_DIR := $(realpath .)
CUR_CXX_DIR := $(subst $(PROJECT_BUILD_ROOT_PATH),$(PROJECT_CODE_ROOT_PATH),$(CUR_DIR))
CXX_SUBDIRS := $(call GetSubDirPaths,$(CUR_CXX_DIR))
CUR_CXXPATH_LIST := $(call GetFilePathsInDir,$(CUR_CXX_DIR),cpp)
CUR_CXXNAME_LIST := $(notdir $(CUR_CXXPATH_LIST))
export PROJECT_CODE_STRUCTURE := $(call GetAllSubDirPaths,$(addprefix $(CUR_CXX_DIR)/,$(CXX_SUBDIRS))) $(call GetAllFilePathsInDir,$(addprefix $(CUR_CXX_DIR)/,$(CXX_SUBDIRS)),*)

vpath %.cpp  $(CUR_CXX_DIR)

all: $(CXX_SUBDIRS) $(patsubst %.cpp,%.o,$(CUR_CXXNAME_LIST)) final

ifneq ($(CXX_SUBDIRS),)
$(CXX_SUBDIRS): $(PROJECT_CODE_STRUCTURE)
	@mkdir -p $@;\
	$(MAKE) -C $@ -f $(PROJECT_MAKEFILES_PATH)/Makefile_subdir;
endif

final: $(PROJECT_CODE_STRUCTURE)
	@echo "All the cpp sourcefiles of the following directory(including subsirectories) have been compiled:"
	@echo "$(CUR_CXX_DIR)"
	@echo "Start to link"
	mkdir -p $@; \
	$(MAKE) -C $@ -f $(PROJECT_MAKEFILES_PATH)/Makefile_$@

ifneq ($(CUR_CXXNAME_LIST),)
-include $(patsubst %.cpp,%.d,$(CUR_CXXNAME_LIST))
endif

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) $(CPPFLAGS) -c $< -MM -MT $*.o -MF $@.$$$$; \
	sed 's,\($*\)\.o[ :],$@ \1\.o:,g' $@.$$$$ > $@; \
	rm -f $@.$$$$;

.PHONY: clean print

clean:
	rm -fr *

print:
	@echo "CXX_SUBDIRS: $(CXX_SUBDIRS)"
	@echo "PROJECT_CODE_STRUCTURE: $(PROJECT_CODE_STRUCTURE)"
	@echo "GetFilePathsInDir: $(call GetFilePathsInDir,$(CUR_CXX_DIR),*)"
	@echo "GetAllFilePathsInDir: $(call GetAllFilePathsInDir,$(CUR_CXX_DIR),*)"
	@echo "PROJECT_EXPECTED_OBJECTPATH_LIST: $(PROJECT_EXPECTED_OBJECTPATH_LIST)"