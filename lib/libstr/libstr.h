/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:06:19 by jaju              #+#    #+#             */
/*   Updated: 2023/08/29 14:13:13 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSTR_H
# define LIBSTR_H

int		str_length(char const *str);
char	*str_substr(char const *str, int start, int end);
int		str_includes(char const *str, char c);
char	*str_tokenize(char *str, char const *delim);
char	*str_replace(char const *str, char const *replaced, char *with);
int		str_equals(char const *a, char const *b);
char	*str_join(char const *a, char const *b);
int		str_indexof(char const *str, char c);
char	*str_clone(char const *str);

#endif
