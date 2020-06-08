MAKE = make --no-print-directory

define ECHO
	@printf "\033[;31m"; printf $1; printf "\033[0m\n"
endef

.PHONY: debug release profile clean clean-all protocol bundle style

debug release profile:
	@$(call ECHO, "[build audp]")
	@$(MAKE) -f mak/audp.mak $@

dist:
	@$(call ECHO, "[build audp]")
	@$(MAKE) -f mak/audp.mak release 

clean:
	@$(call ECHO, "[build audp]")
	@$(MAKE) -f mak/audp.mak $@

	
