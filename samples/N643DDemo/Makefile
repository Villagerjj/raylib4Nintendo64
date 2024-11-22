BUILD_DIR=build
include $(N64_INST)/include/n64.mk

GAME_NAME := RaylibN643DDemo #Sets the name of your rom

src = main.c #defines the main entrypoint file in your project, or the file with all the code

# Recursively find all .png and .glb files inside the assets folder and all of its subdirectories
textures_png = $(wildcard assets/**/**/*.png)
models_glb = $(wildcard assets/**/**/*.glb)
models_gltf = $(wildcard assets/**/**/*.gltf)

# these grab the file paths for each type of asset, and rename them to their converted counterparts. this is used as a list of files to include inside of the DFS (Dragon File System)
textures_conv = $(patsubst assets/%, filesystem/%, $(textures_png:%.png=%.sprite))
models_conv = \
    $(patsubst assets/%, filesystem/%, $(models_glb:%.glb=%.model64)) \
    $(patsubst assets/%, filesystem/%, $(models_gltf:%.gltf=%.model64))

#Idk what this does, and I kinda don't care, because we define all of our texture info in the file names
MKSPRITE_FLAGS ?=

#Tells the compiler that we wanna use raylib
LDFLAGS += -lraylib

#Tells the compiler that we want a .z64 rom
all: $(GAME_NAME).z64

filesystem/%.sprite: assets/%.png	#This converts .png to .sprite
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -v --compress -o "$(patsubst %/,%, $(dir $@))" "$<"

filesystem/%.model64: assets/%.glb	#this converts .glb to .model64, mkmodel seems to only output outside of the filesystem folder, so we need to copy it to the proper location.
	mkdir -p $(dir $@)
	@echo "    [MODEL GLB] $@"
	$(N64_MKMODEL) "$^"
	@mv "$(notdir $(@F))" "$(dir $@)"

filesystem/%.model64: assets/%.gltf	#this converts .gltf to .model64, mkmodel seems to only output outside of the filesystem folder, so we need to copy it to the proper location.
	mkdir -p $(dir $@)
	@echo "    [MODEL GLTF] $@"
	$(N64_MKMODEL) "$^"
	@mv "$(notdir $(@F))" "$(dir $@)"

#[add the rule from the animation demo to include .anim files in the propper locations]

#Debug info, this can be disabled if things get annoying, lists out the original assets, and where they should go in the DFS
$(info Models GLB: $(models_glb))
$(info Models GLTF: $(models_gltf))
$(info Models Conv: $(models_conv))
$(info Textures PNG: $(textures_png))
$(info Textures Conv: $(textures_conv))

#this rule tells make that if we need file_system.dfs (we always do, to make the .z64 rom), we can do so by running the below commands, and by passing in the file paths in the _conv variables.
$(BUILD_DIR)/file_system.dfs: $(textures_conv) $(models_conv)
	@mkdir -p $(dir $@)
	@echo "    [DFS] Creating filesystem $@"
	$(N64_MKDFS) $@ filesystem/

#Similar to the .dfs rule, but makes a .elf file using some mumbo jumbo I don't understand
$(BUILD_DIR)/$(GAME_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

#a rule that tells make to name our game 'RaylibN643DDemo'
$(GAME_NAME).z64: N64_ROM_TITLE="RaylibN643DDemo"
#this is the rule that if we need a .z64 (we do because we ask make to make it), use a file called file_system.dfs to create it.
$(GAME_NAME).z64: $(BUILD_DIR)/file_system.dfs

#a function that cleans some garbage
clean:
	rm -rf $(BUILD_DIR) *.z64

#includes all the .d files in the build folder
-include $(wildcard $(BUILD_DIR)/*.d)

#tells make to run 'all' and 'clean'
.PHONY: all clean
