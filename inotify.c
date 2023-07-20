#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <sys/inotify.h>

#define BUFLEN (16 * (sizeof(struct inotify_event) + 16))

static void usage(const char *pname)
{
	printf("Usage: %s path\n", pname);
	exit(1);
}

static int process_event(const struct inotify_event *ev)
{
	printf("Processing event name: %s\n", ev->name);
	return 0;
}

static int watch_path(const char *path)
{
	char buf[BUFLEN];
	int fd, wd;
	uint32_t mask = (IN_CREATE|IN_DELETE);

	fd = inotify_init();
	if (fd < 0)
	{
		perror("inotify_init");
		return 1;
	}
	wd = inotify_add_watch(fd, path, mask);
	if (wd < 0)
	{
		perror("inotify_add_watch");
		return 1;
	}

	int l, i;
	l = i = 0;
	while (1)
	{
		i = 0;
		memset(buf, 0, sizeof(buf));
		l = read(fd, buf, sizeof(buf)-1);
		if (l <= 0)
		{
			printf("Error reading events\n");
			perror("read");
			return 1;
		}

		while (i < l)
		{
			struct inotify_event *ev = (struct inotify_event *)&buf[i];
			if (!ev->len)
				continue;
			process_event(ev);
			i += (sizeof(struct inotify_event) + ev->len);
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		usage(argv[0]);
	const char *path = argv[1];

	if (watch_path(path) < 0)
	{
		printf("Failed to watch path: %s\n", path);
		return 1;
	}
	return 0;
}
