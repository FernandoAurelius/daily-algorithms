<p align="center">
  <strong>Algorithms – C &amp; Java</strong><br>
  <em>Manual practice of core algorithms</em>
</p>

---

**Prerequisites** (WSL Ubuntu):

```bash
sudo apt update
sudo apt install -y build-essential openjdk-8-jdk openjdk-21-jdk curl git nodejs
```

**Neovim 0.11+**:

```bash
sudo add-apt-repository ppa:neovim-ppa/unstable -y
sudo apt update
sudo apt install -y neovim
```

```bash
nvim --version  # expect v0.11.x+
```

---

**Clone & Structure**:

```bash
git clone https://github.com/FernandoAurelius/algorithms-c-java.git
cd algorithms-c-java
```

```
.
├── c/       # C implementations
├── java/    # Java implementations
└── config/  # Neovim Lua configs
```

---

**Neovim Setup**:

Add to <code>~/.config/nvim/init.lua</code>:

```lua
local lazypath = vim.fn.stdpath("data").."/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({
    "git","clone","--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git", lazypath
  })
end
vim.opt.rtp:prepend(lazypath)
require("config.lazy")
require("config.commands")
```

Add to <code>~/.config/nvim/lua/config/lazy.lua</code>
```
require("lazy").setup({
  -- LSP
  { "neovim/nvim-lspconfig" },
  { "williamboman/mason.nvim"},
  { "williamboman/mason-lspconfig.nvim" },

  -- Autocomplete
  { "hrsh7th/nvim-cmp" },
  { "hrsh7th/cmp-nvim-lsp" },
  { "L3MON4D3/LuaSnip" },

  -- Syntax Highlighting
  { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate" },

  -- Fuzzy finder (optional)
  { "nvim-telescope/telescope.nvim", dependencies = { "nvim-lua/plenary.nvim" } },

  -- Theme (optional)
  { "ellisonleao/gruvbox.nvim", priority = 1000 }
})

-- General configuration
vim.o.number = true
vim.o.relativenumber = true
vim.o.clipboard = "unnamedplus"
vim.cmd.colorscheme("gruvbox")

-- Treesitter
require("nvim-treesitter.configs").setup {
  ensure_installed = { "java", "c", "lua", "vim", "bash" },
  highlight = { enable = true },
}

-- Mason and LSP
require("mason").setup()
require("mason-lspconfig").setup {
  ensure_installed = { "jdtls", "clangd" },
}

local lspconfig = require("lspconfig")
local capabilities = require("cmp_nvim_lsp").default_capabilities()

for _, server in ipairs(require("mason-lspconfig").get_installed_servers()) do
  local opts = { capabilities = capabilities }
  if server == "jdtls" then
    opts.cmd = {
      "/usr/lib/jvm/java-21-openjdk-amd64/bin/java",
      "-Declipse.application=org.eclipse.jdt.ls.core.id1",
      "-Dosgi.bundles.defaultStartLevel=4",
      "-Declipse.product=org.eclipse.jdt.ls.core.product",
      "-Dlog.protocol=true",
      "-Dlog.level=ALL",
      "-Xms1g",
      "--add-modules=ALL-SYSTEM",
      "--add-opens", "java.base/java.util=ALL-UNNAMED",
      "--add-opens", "java.base/java.lang=ALL-UNNAMED",
      "-jar", vim.fn.glob("~/.local/share/nvim/mason/packages/jdtls/plugins/org.eclipse.equinox.launcher_*.jar"),
      "-configuration", vim.fn.expand("~/.local/share/nvim/mason/packages/jdtls/config_linux"),
      "-data", vim.fn.expand("~/.cache/jdtls-workspace")
    }  end

  lspconfig[server].setup(opts)
end

-- Autocomplete
local cmp = require("cmp")
cmp.setup({
  snippet = {
    expand = function(args)
      require("luasnip").lsp_expand(args.body)
    end,
  },
  mapping = cmp.mapping.preset.insert({
    ['<Tab>'] = cmp.mapping.select_next_item(),
    ['<S-Tab>'] = cmp.mapping.select_prev_item(),
    ['<CR>'] = cmp.mapping.confirm({ select = true }),
  }),
  sources = {
    { name = 'nvim_lsp' }
  }
})
```

Add to <code>~/.config/nvim/lua/config/commands.lua</code>
```lua
local map = vim.keymap.set
vim.g.mapleader = " "

map("n", "<leader>r", function ()
	local ft = vim.bo.filetype
	vim.cmd("w")
	if ft == "c" then
		local f = vim.fn.expand("%:t:r")
		vim.cmd("split | terminal gcc % -o " .. f .. " && ./" .. f)
	elseif ft == "java" then 
		local f = vim.fn.expand("%:t:r")
		vim.cmd("split | terminal javac % && java " .. f)
	else
		print("File not supported: " .. ft)
	end
end, { desc = "Compile and run (C/Java)" })
```

Open Neovim and run:

```
:Mason     # install clangd, jdtls
:LspInfo   # verify LSPs attached
```

---

Happy coding!
