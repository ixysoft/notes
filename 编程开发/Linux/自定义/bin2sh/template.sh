#!/bin/sh
__FILE__=`basename $0`
__EXECUTED__=0
if [ $# -eq 0 -a $__EXECUTED__ -eq 0 ];then
    # if in template
    echo "Usage:"
    echo "$0 'binary file path' > 'output path'"
    exit 0
fi
if [ $# -eq 1 ];then
    # create a new sh file
    cat $0|sed 's/^__EXECUTED__=0$/__EXECUTED__=1/'
    # depend on gzip
    gzip -c $1
    exit 0
fi
PROGRAM_BEGIN_LINE=`cat $0|awk '/^_-_-ZDQC-_-_$/{print NR}'`
if [ ! -d /tmp ];then
    mkdir /tmp
    RET=$?
    if [ $RET -ne 0 ];then
        echo "Priviledges not enough"
        exit $RET
    fi
fi
:>/tmp/$__FILE__.x
awk "NR>${PROGRAM_BEGIN_LINE}{print \$0}" $0|gzip -d 2>/dev/null > /tmp/$__FILE__.x
chmod +x /tmp/$__FILE__.x
RET=$?
if [ $RET -ne 0 ];then
    echo "Priviledges not enough"
    exit $RET
fi
/tmp/$__FILE__.x
exit $?
_-_-ZDQC-_-_
