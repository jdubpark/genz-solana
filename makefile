OUT_DIR := ./target/deploy
dummy_build_folder := $(shell mkdir -p $(OUT_DIR))

include ~/.local/share/solana/install/active_release/bin/sdk/sbf/c/sbf.mk
