set nocompatible
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'

" 導入したいプラグインを以下に列挙
" Plugin '[Github Author]/[Github repo]' の形式で記入
Plugin 'airblade/vim-gitgutter'
Plugin 'tomasr/molokai'         " カラースキームmolokai
Plugin 'itchyny/lightline.vim'  " ステータスラインの表示内容強化
Plugin 'bronson/vim-trailing-whitespace'    " 末尾の全角と半角の空白文字を赤くハイライト
Plugin 'Yggdroot/indentLine'    " インデントの可視化
Plugin 'ctrlpvim/ctrlp.vim'         " 多機能セレクタ
Plugin 'tacahiroy/ctrlp-funky'      " CtrlPの拡張プラグイン. 関数検索
Plugin 'suy/vim-ctrlp-commandline'  " CtrlPの拡張プラグイン. コマンド履歴検索
Plugin 'scrooloose/syntastic'       " 構文エラーチェック

call vundle#end()
filetype plugin indent on

" その他のカスタム設定を以下に書く

"----------------------------------------------------------
" molokaiの設定
"----------------------------------------------------------
colorscheme molokai
set t_Co=256 " iTerm2など既に256色環境なら無くても良い
syntax enable " 構文に色を付ける

"----------------------------------------------------------
" ステータスラインの設定
"----------------------------------------------------------
set laststatus=2 " ステータスラインを常に表示
set showmode " 現在のモードを表示
set showcmd " 打ったコマンドをステータスラインの下に表示
set ruler " ステータスラインの右側にカーソルの現在位置を表示する

"----------------------------------------------------------
" CtrlPの設定
"----------------------------------------------------------
let g:ctrlp_match_window = 'order:ttb,min:20,max:20,results:100' " マッチウインドウの設定. 「下部に表示, 大きさ20行で固定, 検索結果100件」
let g:ctrlp_show_hidden = 1 " .(ドット)から始まるファイルも検索対象にする
let g:ctrlp_types = ['fil'] "ファイル検索のみ使用
let g:ctrlp_extensions = ['funky', 'commandline'] " CtrlPの拡張として「funky」と「commandline」を使用

" CtrlPCommandLineの有効化
command! CtrlPCommandLine call ctrlp#init(ctrlp#commandline#id())

" CtrlPFunkyの有効化
let g:ctrlp_funky_matchtype = 'path'

"----------------------------------------------------------
" Syntasticの設定
"----------------------------------------------------------
" 構文エラー行に「>>」を表示
let g:syntastic_enable_signs = 1
" 他のVimプラグインと競合するのを防ぐ
let g:syntastic_always_populate_loc_list = 1
" 構文エラーリストを非表示
let g:syntastic_auto_loc_list = 0
" ファイルを開いた時に構文エラーチェックを実行する
let g:syntastic_check_on_open = 1
" 「:wq」で終了する時も構文エラーチェックする
let g:syntastic_check_on_wq = 1

" c言語用. 構文エラーチェックにsplintを使用
let g:syntastic_c_checkers=['splint']

"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

set encoding=utf-8
scriptencoding utf-8


"=====文字コード=====
set fileencoding=utf-8 				" 保存時の文字コード
set fileencodings=ucs-boms,utf-8,euc-jp,cp932 	" 読み込み時の文字コードの自動判別. 左側が優先される
set fileformats=unix,dos,mac 			" 改行コードの自動判別. 左側が優先される
set ambiwidth=double 				" □や○文字が崩れる問題を解決


"=====タブ・インデント=====
set expandtab 		" タブ入力を複数の空白入力に置き換える
set tabstop=4 		" 画面上でタブ文字が占める幅
set softtabstop=4 	" 連続した空白に対してタブキーやバックスペースキーでカーソルが動く幅
set autoindent 		" 改行時に前の行のインデントを継続する
set smartindent 	" 改行時に前の行の構文をチェックし次の行のインデントを増減する
set shiftwidth=4 	" smartindentで増減する幅


"=====文字列検索=====
set incsearch 		" インクリメンタルサーチ. １文字入力毎に検索を行う
set ignorecase 		" 検索パターンに大文字小文字を区別しない
set smartcase 		" 検索パターンに大文字を含んでいたら大文字小文字を区別する
set hlsearch 		" 検索結果をハイライト

" ESCキー2度押しでハイライトの切り替え
nnoremap <silent><Esc><Esc> :<C-u>set nohlsearch!<CR>


"=====カーソル=====
set whichwrap=b,s,h,l,<,>,[,],~ 	" カーソルの左右移動で行末から次の行の行頭への移動が可能になる
set number 				" 行番号を表示
set cursorline 				" カーソルラインをハイライト

" 行が折り返し表示されていた場合、行単位ではなく表示行単位でカーソルを移動する
nnoremap j gj
nnoremap k gk
nnoremap <down> gj
nnoremap <up> gk

" バックスペースキーの有効化
set backspace=indent,eol,start


"=====カッコ・タグジャンプ=====
set showmatch 				" 括弧の対応関係を一瞬表示する
source $VIMRUNTIME/macros/matchit.vim 	" Vimの「%」を拡張する


"=====コマンド補完=====
set wildmenu 		" コマンドモードの補完
set history=5000 	" 保存するコマンド履歴の数


"=====ペースト設定=====
if &term =~ "xterm"
    let &t_SI .= "\e[?2004h"
    let &t_EI .= "\e[?2004l"
    let &pastetoggle = "\e[201~"

    function XTermPasteBegin(ret)
        set paste
        return a:ret
    endfunction

    inoremap <special> <expr> <Esc>[200~ XTermPasteBegin("")
endif

