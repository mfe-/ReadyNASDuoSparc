#ifndef __HOTPLUS_H__
#define __HOTPLUS_H__

typedef struct padre_hotplug_thread_struct {
        void  (*run) (void *arg);
        wait_queue_head_t       wqueue;
        struct completion       *event;
        const char              *name;
	void 			*data;
} padre_hotplug_thread_t;

extern padre_hotplug_thread_t *
padre_hotplug_thread_init(void (*run) (void *), void *data, const char *name);
extern void padre_wakeup_hotplug_thread(padre_hotplug_thread_t *thread);

#endif
