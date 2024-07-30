DUNE = opam exec -- dune
.DEFAULT_GOAL := help

.PHONY: help
help: ## Print this help message
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: build
build: ## Build the project
	$(DUNE) build

.PHONY: check-npm-deps
check-npm-deps: ## Check if the npm dependencies match Opan requirements
	opam exec opam-check-npm-deps

.PHONY: clean
clean: ## Clean build artifacts and other generated files
	$(DUNE) clean

.PHONY: create-switch
create-switch: ## Create opam switch
	opam switch create . 5.1.1 -y --deps-only

.PHONY: format
format: ## Format the codebase with ocamlformat
	$(DUNE) build @fmt --auto-promote

.PHONY: init
init: create-switch install check-npm-deps ## Configure everything to develop this repository in local, runs `create-switch`, `install`, and `check-npm-deps`

.PHONY: install
install: ## Install development dependencies
	npm install --legacy-peer-deps
	opam update
	opam install -y . --deps-only --with-test
	opam exec opam-check-npm-deps

.PHONY: ngrok
ngrok: ## Forward the locally running application to designsbysm.ngrok.io
	ngrok http 5173 --host-header=\"localhost:5173\" --subdomain=designsbysm

.PHONY: serve
serve: ## Serve the application with a local HTTP server
	npx vite _build/default --open

.PHONY: watch
watch: ## Watch for the filesystem and rebuild on every change
	$(DUNE) build --watch
