#include "cub.h"

void	print_sprite(t_struct *s)
{
		printf("sprite N:%d | ", s->i);
		printf("WallDst = %6.2f | ", s->wall.buf[(s->win.x / 2)]);
		printf("spr Dst = %6.2f | ", s->sprite[s->i].dist);
		printf("d x  = %6.2f | ", s->sprite[s->i].delta.x);
		printf("d y  = %6.2f | ", s->sprite[s->i].delta.y);
		printf("height = %d | ", s->sprite[s->i].height);
		printf("depth x  = %6.2f | ", s->sprite[s->i].depth.x);
		printf("depth y  = %6.2f | ", s->sprite[s->i].depth.y);
		printf("start x = %d | ", s->sprite[s->i].start.x);
		printf("start y = %d | ", s->sprite[s->i].start.y);
		printf("end x = %d | ", s->sprite[s->i].end.x);
		printf("end y = %d\n", s->sprite[s->i].end.y);
}

void	ft_print_arg(t_struct *s)
{
	printf("RESOLUTION : %d x %d\n", s->win.x, s->win.y);
	printf("FLOOR : %d,%d,%d\n", s->floor.r, s->floor.g, s->floor.b);
	printf("SKY : %d,%d,%d\n", s->sky.r, s->sky.g, s->sky.b);
	printf("MAP : %dx%d\n", s->map.x, s->map.y);
	printf("POS : [%.f,%.f]\n", s->p.pos.x, s->p.pos.y);
	printf("DIR : %.f, %.f\n", s->p.dir.x, s->p.dir.y);
	printf("texture width : %d\n", s->tex.width);
	printf("texture N : %p\n", s->tex.n);
	printf("texture s : %p\n", s->tex.s);
	printf("texture e : %p\n", s->tex.e);
	printf("texture w : %p\n", s->tex.w);
	printf("texture S : %p\n", s->tex.sprite);
	print_map(s);
	printf("nb sprite: %d\n", s->map.sprite_nb);
}

void	print_map(t_struct *s)
{
	int i;

	i = 0;
	while (s->map.tab[i])
	{
		printf("%s\n", s->map.tab[i]);
		i++;
	}
}
