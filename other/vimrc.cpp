syntax on

:set tabstop=2 softtabstop=2
:set shiftwidth=2
:set expandtab
:set smartindent
:set nu
:set nowrap
:set incsearch
:set relativenumber

:set colorcolumn=80
highlight ColorColumn ctermbg=0 guibg=lightgrey

" Keybinding for ctrl-a to select all
map <C-a> <esc>ggVG<CR>

execute pathogen#infect()
syntax on
filetype plugin indent on
