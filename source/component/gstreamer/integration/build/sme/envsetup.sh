G_RTDIR_SME=source/sme
G_RTDIR_DEMO=test/sme/test_sme_player
G_RTDIR_LLT=test/sme/llt
G_RTDIR_BUILD=build/sme

#���MediaOS��·����
export MEDIAOS_DIR_STRUCTURE=y
#sme����sdk����ʱΪ�գ�TVOS2.0
#export MEDIAOS_DIR_STRUCTURE=n

G_SME_MAKE=/usr/bin/make

#��ѯ��������
function hsenv() {
cat <<EOF
Invoke ". build/envsetup.sh" from your shell to add the following functions to your environment:
- cmediaos:   Changes directory to the top of the tree(mediaos root tree).
- csme:   Changes directory to the source/sme dir.
- cbuild:   Changes directory to the build/sme dir.
- cdemo:   Changes directory to the test/sme/test_sme_player.
- cut:   Changes directory to the test/llt.
- smmm: build the module designated, for example:smmm libsme_player, and don't build any its depedency
- smmma: build the module designated, for example:smmma libsme_player, and build all its depedency
- sm: build all module below source/sme
- sself: build all self rd lib
- sdemo: build all demo
- sllt:   build all llt
- sshow:   show all module in project

Look at the source to view more functions. The complete list is:
EOF
    T=$(gstsmetop)
    local A
    A=""

    for i in `cat $T/build/sme/envsetup.sh | sed -n "/^function /s/function \([a-z_]*\).*/\1/p" | sort`; do
	A="$A $i"
    done

    echo $A
}

#��ȡ����Ŀ¼����
function gstsmetop
{
    local TOPFILE=build/sme/core/config.mk
    if [ -n "$TOP" -a -f "$TOP/$TOPFILE" ] ; then
        echo $TOP
    else
        if [ -f $TOPFILE ] ; then
            # The following circumlocution (repeated below as well) ensures
            # that we record the true directory name and not one that is
            # faked up with symlink names.
            PWD= /bin/pwd
        else
            local HERE=$PWD
            T=
            while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
                \cd ..
                T=`PWD= /bin/pwd`
            done
            \cd $HERE
            if [ -f "$T/$TOPFILE" ]; then
                echo $T
            fi
        fi
    fi
}

#���Ŀ¼�л�����


function cmediaos()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
        \cd $(gstsmetop)/$1
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

alias csme='cmediaos $G_RTDIR_SME'
alias cdemo='cmediaos $G_RTDIR_DEMO'
alias cllt='cmediaos $G_RTDIR_LLT'
alias cbuild='cmediaos $G_RTDIR_BUILD'

#������뺯��
#$1:ģ����,��ѡ
#$2:-B����ѡ��-B ǿ��ȫ����
function smmm()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
        if [ x$2 = x-B ];then
            if [ x$1 = xall ];then
                $G_SME_MAKE -C $T/$G_RTDIR_BUILD clean
            else
                $G_SME_MAKE -C $T/$G_RTDIR_BUILD $1-prepare-clean
            fi
        fi
        $G_SME_MAKE -C $T/$G_RTDIR_BUILD $1
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

complete -F _smmm smmm
complete -F _smmm smmma

# Tab completion for lunch.
function _smmm()
{
    local cur prev opts
	T=$(gstsmetop)
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
	$G_SME_MAKE -s -C $T/$G_RTDIR_BUILD export_all_modules
    COMPREPLY=( $(compgen -W "`cat ~/.export_all_modules` -B" -- ${cur}) )
    return 0
}

#������뺯��
#$1:ģ����
#$2:-B����ѡ��-B ǿ��ȫ����
function smmma()
{
	Arg1=$1
	Arg1Len=${#Arg1}

    T=$(gstsmetop)
    if [ "$T" ]; then
		if [ x$2 = x-B ];then
			if [ x${Arg1:Arg1Len - 6:6} = x-clean ] || [ x${Arg1:Arg1Len - 14:14} = x-prepare-clean ] || [ x${Arg1:Arg1Len - 10:10} = x-cfg-clean ] ;then
				$G_SME_MAKE -C $T/$G_RTDIR_BUILD $1
				return 0
			fi
			$G_SME_MAKE -C $T/$G_RTDIR_BUILD $1-prepare-clean
		fi
		if [ x${Arg1:Arg1Len - 6:6} = x-clean ] || [ x${Arg1:Arg1Len - 14:14} = x-prepare-clean ] || [ x${Arg1:Arg1Len - 10:10} = x-cfg-clean ] ;then
			$G_SME_MAKE -C $T/$G_RTDIR_BUILD $1
		else
			$G_SME_MAKE -C $T/$G_RTDIR_BUILD $1-deps
		fi
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}


#������뺯��
#$1:-B����ѡ��-B ǿ��ȫ����
function sm()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
		if [ x$1 = x-B ];then
			$G_SME_MAKE -C $T/$G_RTDIR_BUILD clean
		elif [ x$1 = xclean ];then
		        $G_SME_MAKE -C $T/$G_RTDIR_BUILD clean
			return 0
		fi
		$G_SME_MAKE -C $T/$G_RTDIR_BUILD all
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

#������뺯��
#$1:-B����ѡ��-B ǿ��ȫ����
function sself()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
		$G_SME_MAKE -C $T/$G_RTDIR_BUILD all self-rd=y $1
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

#������뺯��
#$1:-B����ѡ��-B ǿ��ȫ����
function sdemo()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
		$G_SME_MAKE -C $T/$G_RTDIR_BUILD all demo=y $1
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

#������뺯��
#$1:-B����ѡ��-B ǿ��ȫ����
function sllt()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
		$G_SME_MAKE -C $T/$G_RTDIR_BUILD all llt=y $1
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}


function sshow()
{
    T=$(gstsmetop)
    if [ "$T" ]; then
		$G_SME_MAKE -C $T/$G_RTDIR_BUILD show_modules
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
}

#$1��bision�������·��
function func_setup_env_bison()
{
	local lcv_gst_parser_bison_path=/usr/bin
	if [ x$1 != x ];then
		lcv_gst_parser_bison_path=$1
	fi
	echo "bsion locate at:$lcv_gst_parser_bison_path"

	local lcv_sys_path_org=$PATH
	local lcv_tmp_path=`echo $lcv_sys_path_org | sed 's/:/ /g'`
	for as_dir in $lcv_tmp_path
	do
		echo as_dir=$as_dir
		if [[ $as_dir != ${lcv_gst_parser_bison_path} ]];then
			echo "set bison path now!"
			echo as_dir=$as_dir
			export PATH=$lcv_gst_parser_bison_path:$PATH
		fi
		break;
	done
}

#$1����Դ��pkg-config·��
function func_setup_env_opensource_pkg_config_path()
{
	local lcv_opensource_pkg_config_path=$1
	if [ x$1 = x ];then
		echo "not set sme opensource pkg-config-path, use default, it will cause compiling error!!!"
	fi
	echo "opensource_pkg_config_path:$lcv_opensource_pkg_config_path"

	local lcv_sys_pkg_config_path_org=$PKG_CONFIG_PATH
	local lcv_tmp_path=`echo $lcv_sys_pkg_config_path_org | sed 's/:/ /g'`
	for as_dir in $lcv_tmp_path
	do
		echo as_dir=$as_dir
		if [[ $as_dir != ${lcv_opensource_pkg_config_path} ]];then
			echo "set sme opensource pkg-config-path now!"
			echo as_dir=$as_dir
			export PKG_CONFIG_PATH=$lcv_opensource_pkg_config_path:$PKG_CONFIG_PATH
		fi
		break;
	done
}

#���û�������
#if [ x$1 = xrls ];then
#    #����ʱ��ȡ�ı��������Ϊrls������release�汾������Ϊdebug�汾��
#    export ENV_SME_VERSION_TYPE=rls;
#elif [ x$1 = xlcov ];then
#    export ENV_SME_VERSION_TYPE=lcov;
#else
#	export ENV_SME_VERSION_TYPE=dbg;
#fi

#$1Ϊproject��Ӧ�������ļ�����ڵ�ǰ���ļ����磺sme��Ŀ¼ʱ��build/sme/project/tvos2.0.sxyx/Hi3796MV100.cfg.mk
#��build/smeʱ��project/tvos2.0.sxyx/Hi3796MV100.cfg.mk
export ENV_SME_CFG_PATH=`pwd`/$1;
echo "ENV_SME_CFG_PATH=$ENV_SME_CFG_PATH"
if [ x$2 = xrls ];then
#����ʱ��ȡ�ı��������Ϊrls������release�汾������Ϊdebug�汾��
	export ENV_SME_VERSION_TYPE=rls;
elif [ x$2 = xlcov ];then
	export ENV_SME_VERSION_TYPE=lcov;
else
	export ENV_SME_VERSION_TYPE=dbg;
fi

func_setup_env_bison /usr/bin