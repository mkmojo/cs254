# Do Not Remove This
source /usr/staff/lib/defaults/system.cshrc


# PATH addition example
setenv PATH "$PATH":"$HOME/bin"

# set default printer ("inner" or "west")
setenv LPDEST inner

# set default editor
setenv EDITOR emacs


# add all INTERACTIVE commands here, specifically, any stty or prompt setting
if ($?prompt) then
	set history = 100

	alias ll ls -l
endif
