# If you cme from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Path to your oh-my-zsh installation.
export ZSH="/Users/ygeslin/.oh-my-zsh"
# zplug
source $ZPLUG_HOME/init.zsh
export ZPLUG_HOME=/usr/local/opt/zplug
export PRINT_ALIAS_PREFIX='  ╰─> '
export PRINT_ALIAS_FORMAT=$'\e[1m'
export PRINT_NON_ALIAS_FORMAT=$'\e[0m'

# Print the full command passed when using aliases
zplug "brymck/print-alias"
# rename automatically windows 
zplug 'sei40kr/zsh-tmux-rename'
# This plugin adds an operation which quotes or unquotes a motion
zplug "zsh-vi-more/vi-quote"
# Add visual information on vi-mode in zsh-shell
zplug "laurenkt/zsh-vimto"
zplug load


# Set name of the theme to load --- if set to "random", it will
# load a random theme each time oh-my-zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/ohmyzsh/ohmyzsh/wiki/Themes
ZSH_THEME="robbyrussell"
plugins=(
	vi-mode
	zsh-z
	git
	clipboard
	iterm2
	osx
	tmux
	kubectl
	zsh-lux
	Colored-man-pages
	Zsh-autosuggestions
	zsh-syntax-highlighting
	git-flow-completion
	brew
	zsh-brew-services
	docker-completion
	#print-alias
	#brew-services
	#you-should-use
	#auto-suggestions
	#auto-completions
	#macos
	#plugin
	#expand
	#ls
	#hints
	#homebrew
	#vi-motions
	#vi-quote
	#vimman
	#zce
)
#unused plugin fzf-zsh
source $ZSH/oh-my-zsh.sh

#kubernetes aliases from https://github.com/ahmetb/kubectl-aliases
[ -f ~/.kubectl_aliases ] && source ~/.kubectl_aliases
function kubectl() { echo "+ kubectl $@">&2; command kubectl $@; }

# Set list of themes to pick from when loading at random
# Setting this variable when ZSH_THEME=random will cause zsh to load
# a theme from this variable instead of looking in ~/.oh-my-zsh/themes/
# If set to an empty array, this variable will have no effect.
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion.
# Case-sensitive completion must be off. _ and - will be interchangeable.
# HYPHEN_INSENSITIVE="true"

# Uncomment the following line to disable bi-weekly auto-update checks.
# DISABLE_AUTO_UPDATE="true"

# Uncomment the following line to automatically update without prompting.
# DISABLE_UPDATE_PROMPT="true"

# Uncomment the following line to change how often to auto-update (in days).
 export UPDATE_ZSH_DAYS=7

# Uncomment the following line if pasting URLs and other text is messed up.
# DISABLE_MAGIC_FUNCTIONS=true

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
 ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
 #COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
 #"mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
# HIST_STAMPS="mm/dd/yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in ~/.oh-my-zsh/plugins/*
# Custom plugins may be added to ~/.oh-my-zsh/custom/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

 #Preferred editor for local and remote sessions
 if [[ -n $SSH_CONNECTION ]]; then
   export EDITOR='vim'
 else
   export EDITOR='nvim'
 fi
# add manpath of Xcode with man2, man 3 and other libc man
export MANPATH="$MANPATH:/Users/ygeslin/man"

## NVM
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

## Vim
alias v="nvim"
alias vi="nvim"
alias vim="nvim"
alias vallc="vim *.c"
alias vallh="vim *.h"
alias vm="vim Makefile"

## aliases
alias c="clear"
 
## Use a long listing format ##
#alias ls="ls"
alias ll="ls -la"
 
## Show hidden files ##
alias l.="ls -d .*"
# create a directory
alias mkdir="mkdir -pv"
# install  colordiff package :)
#alias diff="colordiff"
# handy short cuts #
alias rmrf= "rm -rf "
alias h="history"
alias j="jobs -l"
alias path="echo -e ${PATH//:/\\n}"
alias now="date +"%T""
alias nowtime=now
alias nowdate="date +"%d-%m-%Y""
alias srcz="source ~/.zshrc"
alias srct="tmux source-file ~/.tmux.conf"
# Copy the output in the MacOS buffer
alias copy="| pbcopy"
# Tmux
alias tns="tmux new -s"       # tmux new session
alias tat="tmux attach -t"            # tmux attach
alias tls="tmux ls"                   # list
alias tks="tmux kill-session -s"      # kill session name
alias tkas="pkill -f tmux # kill all tmux session"
#git
alias gac="git add . && git commit -m" 
alias gp="git push"
alias gh="git --help"
alias gl="git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
alias glp="gl -p"
alias gs="git status"
alias gd="git diff --stat"
alias gi="git init"
alias giturl="git@github.com:YG974"
alias gra="git remote add origin"

#makefile
alias mt="make test"
alias mr="make re"
alias ma="make all"
alias mc="make clean"
alias mfc="make fclean"

# Config files
alias pushconfig="sh ~/dotfiles/update_dotfile.sh"
alias vimconf="vim ~/.config/nvim/init.vim"
alias tmuxconf="vim ~/.tmux.conf"
alias zshconf="vim ~/.zshrc"
alias vimhist="vim ~/.zsh_history"

# minikube aliases
alias mk="minikube"
alias mkss="minikube status"
alias mkst="minikube start"
alias mksp="minikube stop"
alias mkd="minikube delete"
alias mksv="minikube service"
alias mkde="minikube docker-env"

# Docker aliases
alias dockerapp="open /Applications/Docker.app"
alias d="docker"
alias dl="docker ps -l -q"
alias di="docker images"
alias dia="docker images -a"
alias dps="docker ps"
alias dpsa="docker ps -a"
alias drm="docker rm"
alias drmi="docker rmi"
alias drmall="docker rmi $(docker images -a -q) && docker rm $(docker ps -aq)"
alias dsp="docker system prune"
alias dbt="docker build -t"
alias drti="docker run --rm -it"
alias drp80="docker run -p 80:80"
alias drp80443="docker run -p 80:80 -p 443:443"
alias drpd80="docker run -d -p 80:80"
alias drpd80443="docker run -p 80:80 -p 443:443"

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#
# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"

. /usr/local/etc/profile.d/z.sh
[ -f ~/.fzf.zsh ] && source ~/.fzf.zsh

# for zsh completion, see gitpage zsh-completion
autoload -U compinit && compinit
#To apply the command to CTRL-T as well
export FZF_DEFAULT_COMMAND='fd --type f --hidden --follow -E ~/.fdignore'
export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"

## Use Vim for command line prompt
autoload -U edit-command-line
zle -N edit-command-line
bindkey '^x^x' edit-command-line
alias norminette="~/.norminette/norminette.rb"
bindkey -v
#bindkey '^R' history-incremental-search-backward
set show-mode-in-prompt on
set editing-mode vi
set keymap vi
alias norminette="~/.norminette/norminette.rb"
