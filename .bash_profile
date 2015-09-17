if [ -f /etc/bashrc ]; then  
    . /etc/bashrc
fi

alias ls='ls -FGh --color'
alias f26='ssh qqiu@f26.cs.rochester.edu'
alias goqqy='ssh root@goqqy.tk'
alias cycle1='ssh qqiu@cycle1.cs.rochester.edu'
alias cs258='ssh -l cs258 cycle2.csug.rochester.edu'
alias cs458='ssh -l cs458 cycle2.cs.rochester.edu'
alias blue='ssh   qqiu2@bluehive.circ.rochester.edu'
alias blued='ssh -D 1024  qqiu2@bluehive.circ.rochester.edu'
alias bluex='ssh -X  qqiu2@bluehive.circ.rochester.edu'
alias tf='cd ~/workspace/treeframework'
alias hp='cd /u/www/users/grads/qqiu' #homepage
alias ipyspark='IPYTHON=1 /u/qqiu/spark-1.4.0-bin-hadoop2.6/bin/pyspark --master yarn-client'

export PYTHONPATH="/u/qqiu/usr/local/matplotlib/lib/python2.7/site-packages"
export PATH="/u/qqiu/usr/local/dropbox/bin:${PATH}"
export PATH="~/usr/bin:${PATH}"
export PATH="/u/qqiu/spark-1.4.0-bin-hadoop2.6/bin:${PATH}"
export PATH="/u/qqiu/usr/local/mpich-3.1.3/bin:${PATH}"
export PATH="/u/qqiu/usr/toolworks/totalview.8.14.1-8/bin:${PATH}"
export PATH="/u/qqiu/hadoop-2.6.0/bin:${PATH}"
export PATH="/u/qqiu/usr/local/zsh-5.0.8/bin:${PATH}"
export PATH="/u/qqiu/usr/local/postgresql-9.4.4/bin:${PATH}"
export PATH="/u/qqiu/usr/local/fish-2.1.2/bin:${PATH}"
export PATH="/u/qqiu/usr/local/apache-maven-3.3.3/bin:${PATH}"
export PATH="/home/vax7/u27/qqiu/usr/local/scala-2.11.6/bin:${PATH}"
export PATH="/u/cs254/bin/:${PATH}"
export CUPS_SERVER="print.cs.rochester.edu"
export PRINTER="chaucer"
export JAVA_HOME="/usr/lib/jvm/java-1.7.0/"
export PATH="$HOME/usr/local/java-1.7.0/bin:$PATH"
#export JAVA_HOME="$HOME/usr/local/jdk1.7.0_79"
#export PATH="$HOME/usr/local/jdk1.7.0_79/bin:$PATH"

export HADOOP_HOME=$HOME/hadoop-2.6.0
export HADOOP_MAPRED_HOME=$HADOOP_HOME 
export HADOOP_COMMON_HOME=$HADOOP_HOME 
export HADOOP_HDFS_HOME=$HADOOP_HOME 
export YARN_HOME=$HADOOP_HOME 
export HADOOP_CONF_DIR=$HADOOP_HOME/etc/hadoop
export YARN_CONF_DIR=$HADOOP_HOME/etc/hadoop 
export HADOOP_COMMON_LIB_NATIVE_DIR=$HADOOP_HOME/lib/native
export HADOOP_OPTS="$HADOOP_OPTS -Djava.library.path=$HADOOP_HOME/lib"
export HADOOP_LOG_DIR=/localdisk/$USER/logs/data
export YARN_LOG_DIR=/localdisk/$USER/logs/yarn
