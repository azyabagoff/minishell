/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:01:59 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:50:06 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

enum e_token
{
	TK_L,
	TK_LL,
	TK_R,
	TK_RR,
	TK_CHAR,
	TK_SPACE,
	TK_PIPE,
	TK_VAR ,
	TK_DVAR,
	TK_FILE,
	TK_RED= TK_L | TK_LL | TK_R | TK_RR
};
enum e_stt
{
	NONE,
	W,
	SP,
	PIPE,
	SQ,
	DQ,
	VAR,
	DVAR
};
typedef struct s_st
{
	t_list				*token_list;
	size_t				pos;
	size_t				i;
	char				*str;
	enum e_stt			stt;
	int					flag;
}						t_st;
typedef struct s_func
{
	int					(*if_stt[10])(t_st	*);
	void				(*add_stt[8])(t_st	*);
}						t_func;
typedef struct s_do
{
	void				(*do_stt[10])(t_st *, void (*add_stt)(t_st *));
}						t_do;
typedef struct s_token
{
	enum e_token	type;
	char			*var;
}					t_token;
int			if_var(t_st *state);
int			if_sp(t_st *state);
int			if_pipe(t_st *state);
int			if_sq(t_st *state);
int			if_dq(t_st *state);
int			if_word(t_st *state);
int			if_pre_var(t_st *state);
int			if_red(t_st *state);
int			if_end(t_st *state);
int			if_none(t_st *state);
void		do_var(t_st *state, void (*add_stt)(t_st*));
void		do_sp(t_st *state, void (*add_stt)(t_st*));
void		do_pipe(t_st *state, void (*add_stt)(t_st*));
void		do_sq(t_st *state, void (*add_stt)(t_st*));
void		do_dq(t_st *state, void (*add_stt)(t_st*));
void		do_word(t_st *state, void (*add_stt)(t_st*));
void		do_pre_var(t_st *state, void (*add_stt)(t_st*));
void		do_red(t_st *state, void (*add_stt)(t_st*));
void		do_end(t_st *state, void (*add_stt)(t_st*));
void		do_none(t_st *state, void (*add_stt)(t_st*));
void		add_var(t_st *state);
void		add_sp(t_st *state);
void		add_pipe(t_st *state);
void		add_word(t_st *state);
void		add_none(t_st *state);
void		error_parser(void);
t_list		**token(char *line);

#endif