/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_heart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:20:20 by jbyttner          #+#    #+#             */
/*   Updated: 2016/05/05 13:28:47 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		heart(vec3 p)
{
	vec3	p2;
	float	z3;

	p2 = pow(p, VEC3(2));
	z3 = pow(p.y, 3);
	return (-(pow((p2.x + (9.0 / 4.0) * p2.z) + p2.y - 1, 3)
		- p2.x * z3 - (9.0 / 80.0) * p2.z * z3));
}

vec3		heart_grad(vec3 p)
{
	vec2	q;

	q = VEC2(0.0, 0.006);
	return (VEC3(heart(p + q.yxx) - heart(p - q.yxx),
			heart(p + q.xyx) - heart(p - q.xyx),
			heart(p + q.xxy) - heart(p - q.xxy)));
}

s_res		end_heart(s_geo_cam gc, float step, s_res ret, vec4 p)
{
	float	tmp;
	int		i;

	i = 0;
	step = -step / 2;
	while (++i < 20)
	{
		ret.dst += step;
		p.xyz = gc.cam.pos + ret.dst * gc.cam.ray;
		tmp = p.w;
		p.w = heart((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds);
		if (sign(tmp) != sign(p.w))
			step = -step / 2;
	}
	ret.cam = gc.cam;
	ret.mat = gc.sp.mat;
	ret.normal = normalize(-heart_grad((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds));
	return (ret);
}

s_res		heart_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;

	step = 0.2 / 5;
	ret.dst = length(cam.pos - sp.pos) <= sp.bounds ?
		0 : sphere_dst(sp, cam, prev).dst;
	if (ret.dst == prev.dst)
		return (prev);
	p.xyz = cam.pos + ret.dst * cam.ray;
	p.w = heart((p.xyz - sp.pos) * 5 / sp.bounds);
	i = -1;
	while (++i < INT(30 * sp.bounds) && p.w <= 0)
	{
		p.w = heart((p.xyz - sp.pos) * 5 / sp.bounds);
		ret.dst += 0.2 / 5;
		p.xyz = cam.pos + ret.dst * cam.ray;
	}
	if (p.w < 0)
		return (prev);
	ret = end_heart(geo_cam(sp, cam), step, ret, p);
	if (prev.dst > 0 && ret.dst > prev.dst)
		return (prev);
	return (ret);
}
