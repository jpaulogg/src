-- load standard vis module, providing parts of the Lua API
require('vis')

vis.ftdetect.filetypes.text.cmd = { "set expandtab", }

-- PLUGINS --------------------------------------------------------------------
require('plugins/surround')
require('plugins/statusline')
require('plugins/ins-completion')

-- EVENTOS --------------------------------------------------------------------

-- inicialização
vis.events.subscribe(vis.events.INIT, function()
  	vis:command('set theme zenburn_alpha')
	vis:command('set autoindent')
	vis:command('set tabwidth 4')
end)

-- ao abrir uma janela
vis.events.subscribe(vis.events.WIN_OPEN, function(win)
	vis:command('set relativenumbers')
end)

-- COMANDOS -------------------------------------------------------------------

vis:command_register('Sp', function(argv) -- Split
	local file = vis.win.file
	local path = argv[1] or file.path
	local cmd = string.format([[!/bin/sh -c "st -e vis '%s' &"]], path)
	vis:command(cmd)
end, "Abrir arquivo em nova janela de terminal")

-- ATALHOS DE TACLADO ---------------------------------------------------------

-- clipboard
vis:map(vis.modes.VISUAL, 'D', '"+d') 
vis:map(vis.modes.VISUAL, 'Y', '"+y')
vis:map(vis.modes.VISUAL, 'P', '"+p')

-- usando "alt" como "escape"
vis:map(vis.modes.INSERT, '<M-u>', '<Escape>u')
vis:map(vis.modes.INSERT, '<M-j>', '<Escape>j')
vis:map(vis.modes.INSERT, '<M-k>', '<Escape>k')
vis:map(vis.modes.INSERT, '<M-h>', '<Escape>h')
vis:map(vis.modes.INSERT, '<M-l>', '<Escape>l')

-- mapear "!" como "|" para facilitar a vida quando o teclado não tiver "|"
vis:map(vis.modes.NORMAL, '!', '|')
vis:map(vis.modes.VISUAL, '!', '|')

-- anular J no modo visual
vis:map(vis.modes.VISUAL, 'J', 'j')

-- ignore case
vis:map(vis.modes.NORMAL, 'g/', '<vis-search-forward>(?i)')
