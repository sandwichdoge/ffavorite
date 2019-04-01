SUBDIRS := gen src client

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -k -C $$dir; \
    done
