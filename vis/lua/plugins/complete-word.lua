-- complete word at primary selection location using vis-complete(1)

vis:map(vis.modes.INSERT, "<C-x><C-n>", function()
	local win = vis.win
	local file = win.file
	local pos = win.selection.pos
	if not pos then return end
	local range = file:text_object_word(pos > 0 and pos-1 or pos);
	if not range then return end
	if range.finish > pos then range.finish = pos end
	if range.start == range.finish then return end
	local prefix = file:content(range)
	if not prefix then return end
	local cmd = "vis-complete -p 'word:' --word " .. prefix:gsub("'", "'\\''")
	local status, out, err = vis:pipe(file, { start = 0, finish = file.size }, cmd)
	if status ~= 0 or not out then
		if err then vis:info(err) end
		return
	end
	if vis.mode == vis.modes.INSERT then
		vis:insert(out)
	elseif vis.mode == vis.modes.REPLACE then
		vis:replace(out)
	end
end, "Complete word in file")
