require("lazy").setup({
  -- LSP
  { "neovim/nvim-lspconfig" },
  { "williamboman/mason.nvim"},
  { "williamboman/mason-lspconfig.nvim" },

  -- Autocomplete
  { "hrsh7th/nvim-cmp" },
  { "hrsh7th/cmp-nvim-lsp" },
  { "L3MON4D3/LuaSnip" },
  { "hrsh7th/nvim-cmp", deps = { "hrsh7th/cmp-nvim-lsp" } },

  -- Syntax Highlighting
  { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate" },

  -- Fuzzy finder (opcional)
  { "nvim-telescope/telescope-file-browser.nvim", dependencies = { "nvim-lua/plenary.nvim" } },

  -- Theme (opcional)
  { "ellisonleao/gruvbox.nvim", priority = 1000 },

  -- Autopairs/tag/colorpicker etc.
  { "windwp/nvim-autopairs", config = true },
  { "windwp/nvim-ts-autotag", config = true },
  { "catgoose/nvim-colorizer.lua",
    event = "BufReadPre",
    opts = {
      filetypes = { "*" },
      user_default_options = {
        names = true,
        RGB = true,
        RRGGBB = true, RRGGBBAA = false,
        rgb_fn = true, hsl_fn = true,
        css = true, css_fn = true,
        mode = "background",
        tailwind = true,
        virtualtext = "■",
      },
    },
    config = function(_, opts)
      require("colorizer").setup(opts)
      vim.keymap.set("n", "<leader>ct", "<CMD>ColorizerToggle<CR>", { desc = "[C]olorizer [T]oggle" })
    end,
  },

  -- UI & navigation
  { "onsails/lspkind-nvim" },
  { "nvim-tree/nvim-web-devicons", opts = {} },
  {
    "akinsho/nvim-bufferline.lua",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = true,
  },
  { "glepnir/lspsaga.nvim", branch = "main", config = true },

  -- Formatting
  { "MunifTanjim/prettier.nvim" },
  { "nvimtools/none-ls.nvim",
    branch = "main",
    dependencies = { "nvim-lua/plenary.nvim", "nvimtools/none-ls-extras.nvim" },
  },
})

-- Configuração geral
vim.o.number = true
vim.o.relativenumber = true
vim.o.clipboard = "unnamedplus"
vim.cmd.colorscheme("gruvbox")

-- Treesitter
require("nvim-treesitter.configs").setup {
  ensure_installed = { 
     "java",
     "c", 
     "lua", 
     "vim", 
     "bash", 
     "javascript", 
     "typescript", 
     "tsx", 
     "html", 
     "css", 
     "json", 
  },
  highlight = { enable = true },
}

-- Mason e LSP
require("mason").setup()
require("mason-lspconfig").setup {
   ensure_installed = { 
      "jdtls", 
      "clangd", 
      "vuels", 
      "ts_ls", 
      "cssls", 
      "html", 
      "jsonls",
      "eslint",
      "tailwindcss"
   },
   handlers = {},
}

local lspconfig = require("lspconfig")
local capabilities = require("cmp_nvim_lsp").default_capabilities()

local on_attach = function(client, bufnr)
   if client.server_capabilities.documentFormattingProvider then
      vim.api.nvim_create_autocmd("BufWritePre", {
         buffer = bufnr,
	 callback = function() vim.lsp.buf.format({ bufnr = bufnr }) end,
      })
   end
   require("lspsaga").setup({})
end

for _, srv in ipairs({ "ts_ls", "eslint", "tailwindcss", "html", "cssls", "jsonls" }) do
   lspconfig[srv].setup({ on_attach = on_attach, capabilities = capabilities })
end

local null_ls = require("null-ls")

null_ls.setup({
  sources = {
    null_ls.builtins.formatting.prettier.with({
       extra_filetypes = { "toml", "html", "css", "ts", "tsx" },
    }),
    require("none-ls.diagnostics.eslint"),  
  },
  on_attach = on_attach,
})

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
    } end

  lspconfig[server].setup(opts)
end

lspconfig.vuels.setup({
   capabilities = capabilities,
})

require('lspconfig').ts_ls.setup({
   capabilities = capabilities,
   filetypes = { "typescript", "javascript", "javascriptreact", "typescriptreact", "vue" },
})

-- Autocomplete
local cmp = require("cmp")
local luasnip = require("luasnip")
require("luasnip.loaders.from_vscode").lazy_load()

cmp.setup({
  snippet = {
    expand = function(args)
      luasnip.lsp_expand(args.body)
    end,
  },
  formatting = {
    format = require("lspkind").cmp_format({
      mode = "symbol_text",
      preset = "codicons",
      maxwidth = 50,
      menu = {
        buffer = "[BUF]",
        nvim_lsp = "[LSP]",
        luasnip = "[SNIP]",
        path = "[PATH]",
      },
    }),
  },
  mapping = {
    ["<Tab>"] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_next_item()
      elseif luasnip.expand_or_jumpable() then
        luasnip.expand_or_jump()
      else
        fallback()
      end
    end, { "i", "s" }),
    ["<S-Tab>"] = cmp.mapping(function(fallback)
      if cmp.visible() then
        cmp.select_prev_item()
      elseif luasnip.jumpable(-1) then
        luasnip.jump(-1)
      else
        fallback()
      end
    end, { "i", "s" }),
    ["<CR>"] = cmp.mapping.confirm({ select = true }),
  },
  sources = {
    { name = "nvim_lsp" },
    { name = "luasnip" },
    { name = "buffer" },
    { name = "path" },
  },
})
