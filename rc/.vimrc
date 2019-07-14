""""""""""""""""""""""
" PACKAGE MANAGEMENT "
""""""""""""""""""""""
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'fatih/vim-go'
Plugin 'fatih/molokai'
Plugin 'morhetz/gruvbox'
Plugin 'dracula/vim'
Plugin 'fugitive.vim'
Plugin 'vim-syntastic/syntastic'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
"Plugin 'junegunn/fzf.vim'
"Plugin 'itchyny/lightline.vim'

call vundle#end()

"""""""""""""""""""
" GENERAL SETTING "
"""""""""""""""""""
filetype off                    " Reset filetype detection first ...
filetype plugin indent on       " ... and enable filetype detection
set nocompatible                " Enables us Vim specific features
set ttyfast                     " Indicate fast terminal conn for faster redraw
set ttymouse=xterm2             " Indicate terminal type for mouse codes
set ttyscroll=3                 " Speedup scrolling
set laststatus=2                " Show status line always
set encoding=utf-8              " Set default encoding to UTF-8
set autoread                    " Automatically read changed files
set autoindent                  " Enabile Autoindent
set backspace=indent,eol,start  " Makes backspace key more powerful.
set incsearch                   " Shows the match while typing
set hlsearch                    " Highlight found searches
set noerrorbells                " No beeps
"set number                      " Show line numbers
set showcmd                     " Show me what I'm typing
set noswapfile                  " Don't use swapfile
set nobackup                    " Don't create annoying backup files
set splitright                  " Vertical windows should be split to right
set splitbelow                  " Horizontal windows should split to bottom
set autowrite                   " Automatically save before :next, :make etc.
set hidden                      " Buffer should still exist if window is closed
set fileformats=unix,dos,mac    " Prefer Unix over Windows over OS 9 formats
set noshowmatch                 " Do not show matching brackets by flickering
set noshowmode                  " We show the mode with airline or lightline
set ignorecase                  " Search case insensitive...
set smartcase                   " ... but not it begins with upper case
set completeopt=menu,menuone    " Show popup menu, even if there is one entry
set pumheight=10                " Completion window max size
set nocursorcolumn              " Do not highlight column (speeds up highlighting)
set nocursorline                " Do not highlight cursor (speeds up highlighting)
set lazyredraw                  " Wait to redraw
set ts=2                        " Tab size
set shiftwidth=2                " Tab indent
set expandtab ts=2 sw=2 ai      " Replace tab to space
set nu                          " Display line number

""""""""""""""""
" COLOR SCHEME "
""""""""""""""""
"let g:gruvbox_italic=1
"set background=dark             " Setting dark mode
"set t_Co=256
set termguicolors
"colorscheme gruvbox
syntax on
"let g:rehash256 = 1
"let g:molokai_original = 1
colorscheme dracula
hi DiffDelete ctermbg=0 ctermfg=1
hi DiffAdd ctermbg=2 ctermfg=0
hi DiffChange ctermbg=3 ctermfg=0
hi DiffText ctermbg=3 ctermfg=0
hi DiffDelete ctermbg=0 ctermfg=7
set statusline=%f

""""""""""
" PLUGIN "
""""""""""
" vim-go
nnoremap <c-]> :GoDef<CR>

" FZF
set rtp+=/usr/local/opt/fzf
nnoremap <F2> :FZF<CR>
let g:fzf_action = {
  \ 'ctrl-t': 'tab split',
  \ 'ctrl-i': 'split',
  \ 'ctrl-v': 'vsplit' }

nnoremap <F3> :set nohlsearch<CR>

" syntastic
let g:syntastic_cpp_checkers = ['cpplint']
"let g:syntastic_cpp_cpplint_exec = 'cpplint --filter=-legal/copyright'
"let g:syntastic_cpp_cpplint_exec = 'cpplint'
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_always_populate_loc_list = 1

"set statusline+=%#warningmsg#
"set statusline+=%{SyntasticStatuslineFlag()}
"set statusline+=%*
