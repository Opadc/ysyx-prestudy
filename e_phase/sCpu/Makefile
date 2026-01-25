TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert --trace-fst 

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

YOSYS_SCRIPT_DIR = /home/d5/software/yosys-sta/
export PATH := /home/d5/software/oss-cad-suite/bin:$(PATH)
PROJ_PATH = $(shell pwd)
SHELL := /bin/bash

O ?= $(PROJ_PATH)/result
DESIGN ?= top
SDC_FILE ?= $(PROJ_PATH)/scripts/default.sdc
RTL_FILES ?= $(shell find $(PROJ_PATH)/vsrc -name "*.v")
export CLK_FREQ_MHZ ?= 500
export CLK_PORT_NAME ?= clk
PDK = icsprout55

RESULT_DIR = $(O)/$(DESIGN)-$(CLK_FREQ_MHZ)MHz
SCRIPT_DIR = $(YOSYS_SCRIPT_DIR)/scripts
NETLIST_SYN_V   = $(RESULT_DIR)/$(DESIGN).netlist.v
TIMING_RPT = $(RESULT_DIR)/$(DESIGN).rpt

default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

syn: $(NETLIST_SYN_V)
$(NETLIST_SYN_V): $(RTL_FILES) $(SCRIPT_DIR)/yosys.tcl
	mkdir -p $(@D)
	echo tcl $(SCRIPT_DIR)/yosys.tcl $(DESIGN) $(PDK) \"$(RTL_FILES)\" $@ | yosys -g -l $(@D)/yosys.log -s -



$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

all: default

run: $(BIN)
	@$^

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run
