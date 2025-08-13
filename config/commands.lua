local map = vim.keymap.set
vim.g.mapleader = " "

map("n", "<leader>r", function ()
	local ft = vim.bo.filetype
	vim.cmd("w")
	if ft == "c" then
		local f = vim.fn.expand("%:t:r")
		vim.cmd("split | terminal gcc % -o " .. f .. " -lm && ./" .. f)
	elseif ft == "java" then 
		local f = vim.fn.expand("%:t:r")
		vim.cmd("split | terminal javac % && java " .. f)
	else
		print("File not supported: " .. ft)
	end
end, { desc = "Compile and run (C/Java)" })

map("n", "<S-A-F", function()
   vim.lsp.buf.format({ async = true })
end, { noremap = true, silent = true, desc = 'Format buffer' })

