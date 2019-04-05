SUBDIRS := gen src client

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

install:
	for dir in $(SUBDIRS); do \
        $(MAKE) install -k -C $$dir; \
    done


clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -k -C $$dir; \
    done
