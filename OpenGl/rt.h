/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:50:48 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/22 17:26:56 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <OpenGL/gl3.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# define P_NAME "foobar"
# define BUFF_LENGTH 1024

void				err(char *msg);
void				load_file(char *file, GLchar **ptr, GLint *length);
GLuint				shader(GLenum t, GLsizei c, GLchar **s, GLint *l);
GLuint				shader_program(GLuint *shaders, size_t size);
GLuint				vao(void);
void				vao_add_indices(GLuint vao, GLuint vbo);
void				vao_add_vdata(GLuint vao, GLuint vbo, GLint s, GLboolean n);
GLuint				vbo(GLenum t, GLsizeiptr s, GLvoid *d, GLenum u);
GLuint				index_buffer(GLvoid *d, GLsizeiptr s);
GLuint				data_buffer(GLvoid *d, GLsizeiptr s);

#endif