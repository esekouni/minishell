/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:46:04 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 16:05:16 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

typedef enum e_redir
{
	heredoc,
	append,
	write_inf,
	read_fromf
}	t_redir;

typedef struct s_redirection
{
	char					*file;
	int						type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_arguments
{
	char				*arg;
	struct s_arguments	*next;
}	t_arguments;

typedef struct s_environment_path
{
	char						*variable;
	char						*valeur;
	int							c;
	struct s_environment_path	*next;
}	t_environment_path;

typedef struct s_command_line
{
	char					*command;
	t_redirection			*redirection;
	t_arguments				*args;
	int						heredoc_fd;
	struct s_command_line	*next;
}	t_command_line;

typedef struct s_variables
{
	int				i;
	int				j;
	int				k;
	int				double_cote;
	int				single_cote;
	int				counter;
	int				count;
	int				lenth;
	int				len;
	int				token_lenth;
	int				token_start;
	int				error;
	int				path_exist;
	int				fd;
	int				cote;
	int				path_len;
	int				tot_len;
	int				strs_len;
	int				command_num;
	int				fd_out;
	int				fd_in;
	int				comm_count;
	int				g;
	int				rffile;
	int				wifile;
	int				status;
	int				token_num;
	int				last_exit;
	int				amb_red;
	int				yes;
	unsigned long	v;
	int				tmp_stat;
}	t_variables;

typedef struct s_glob
{
	t_command_line		*command_line;
	t_environment_path	*envp;
	t_environment_path	*export;
	int					exit_stat;
	int					amb_red;
}	t_glob;

char				*after_dollar(char *ch, t_environment_path *enp);
int					ambiguous_redirect(char **tokens);
void				add_variable_existe(t_glob **glob, char *args);
void				add_variable_not_existe(t_glob **glob, char *args);
char				*before_dollar(char *ch);
int					check_special_car(char input);
int					check_special_caracter(char c);
int					check_caractere(char *ch, char c);
int					check_for_cotes(char *av, int i);
int					check_syntax(char *av);
int					check_syntaxe_export(char *args);
int					check_dollar(char *ch);
char				*cat_string_start_end(char *tokens, int start, int end);
char				*cotes_terminator(char *input);
t_command_line		*create_addback_commandline(t_command_line *cmm_line);
t_arguments			*create_addback_arguemts(t_arguments *arguments);
t_redirection		*create_addback_redirection(t_redirection *redirection);
char				*check_cotes_after_dollar(char *split, \
					t_variables *var, char before);
char				*check_after_dollar(char *split, char before, \
					t_variables *variable, t_glob *glob);
char				*create_valeur_export(char *env);
char				*create_valeur(char *env);
char				*command_path(t_environment_path *envp, char *command);
char				*expantion(char *tokens, t_glob *glob);
void				expantion_single_cote(char **join, char *tokens, \
					t_variables	*var);
int					existe_of_variable(t_environment_path *export, \
					char *variable);
int					ft_strlen(char *string);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_unset(t_glob **glob, t_arguments *arguments);
char				*fill_filtred_string(char *tokens, char *filtred_dollar);
char				*filter_dollar(char *tokens);
int					ft_strlen_filter_dollar(char *tokens);
int					ft_export(t_arguments *arguments, t_glob **glob);
void				ft_free(char **split);
t_environment_path	*ft_lst_new_export(char *enp);
char				*ft_strchr(char *str, char n);
char				*ft_strjoin_max(char *s1, char *s2, char *s3);
t_environment_path	*ft_lstlast(t_environment_path *lst);
int					ft_lstsize(t_environment_path *export);
t_environment_path	*ft_lstadd_back(t_environment_path *lst, \
					t_environment_path *new);
t_environment_path	*ft_lst_new(char *ch);
char				*ft_sssstrjoin(char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char *s, char c);
char				*ft_itoa(int n);
char				*ft_strdup(char *string);
int					ft_echo(t_arguments *argument);
int					ft_env(t_environment_path *env);
char				**giga_splite(char *input);
void				here___doc(t_glob *glob);
int					here_ddoc(char *del, int i, t_glob *glob);
t_environment_path	*init_environment_path(char **enp, \
					t_environment_path *envi_path);
t_environment_path	*init_export(char **enp, t_environment_path *export);
char				**join_args(char *command, t_arguments *s_args);
char				**join_envp(t_environment_path *s_envp);
char				*names_generator(int i);
char				*name_variable(char *split, t_variables *variable_index);
char				*name_variable_export(char *split);
char				*print_valeur_dollar(char *split, char before, \
					t_glob *glob, t_variables *var);
char				*path_error(char *path);
char				*remplace_varible_value(char *args, \
					t_environment_path *exp);
int					syntax_error(char *av, int i);
char				**split_afexp(char **strs, int index);
int					tokens_counter(char *input);
int					token_lenth_counter(char *input, int i);
t_command_line		*tokens_identifier(char **tokens);
int					ft_cd(t_glob **glob);
char				*add_double_cotes(char *str);
int					ft_pwd(t_environment_path *envp);
void				free_double_pointer(char **paths);
void				free_pointer(char **ptr);
char				**ft_ssssplit(char *s, char c);
int					ft_exit(t_arguments *args, t_glob **glob);
int					words_count(const char *s, char c);
void				free_command_line(t_command_line *command_line);
void				env_exp_free(t_environment_path *envp, \
					t_environment_path *exp);
void				ft_putstr_fd(char *s, int fd);
void				print_error(char *s1, char *s2);
int					check_exist_and_permission(char *file, int type);
int					check_exist_and_permission_inchild(char *file, int type);
int					check_valid_caractr(char c);
char				*remove_non_printibale(char *join, char c);
void				look_for_path(t_environment_path **tmp, \
					t_variables *var, char ***paths);
void				is_der_or_isnt_reg(char *command, struct stat file_state);
void				expantion_caracter_heredoc(char *tokens, char **join, \
					t_variables *var);
void				join_variable_with_other_value(t_variables *var, \
						char **join, char *input);
int					check_if_cotes_exist(t_variables *var, char *token);
int					only_spaces(char *input);
void				non_builtins(t_glob **glob, int comm_count, int *p);
void				check_redirect_in_child(t_variables *var, \
					t_redirection **tmp2, t_command_line **tmp);
void				also_builtings_in_child(t_glob **glob, \
					t_command_line **tmp);
void				builtings_in_child(t_glob **glob, \
					t_command_line **tmp);
void				send_to_execve(t_glob **glob, t_command_line **tmp, \
									t_variables *var);
void				sig_handler(int signum);
char				*rm_spcs(char *str);
int					should_rm_spcs(char *token, int dolr_indx);
char				*found_valeur_variable(t_environment_path *expo, \
					char *variable);
char				*add_nprin(char *valeur);
char				*remplace_space_nonprint(char *tokens);
int					lent_split(char **split);
int					only_spaces(char *input);
void				expantion_ambiguous_redirect(char ***tokens, t_glob *glob);
void				the_executer(t_glob **glob);
void				call_exec_free_cmmline(t_glob **glob, char ***tokens);
t_glob				*init_glob(char	**envp);
long				ft_atoi(char *str);
void				affiche_export(t_glob *glob);
void				ft_print_valeur(char *valeur, int *cote);
void				free_varibl(t_environment_path **tmp, t_glob **glob);
void				ft_free_env(t_environment_path **env);
void				controll_d_case(t_glob **glob, t_variables *var);
void				split_input_and_ambg(char ***tokens, \
					char **input, t_glob **glob);
int					call_read_input(char **input, t_glob **glob, \
					t_variables *var);
void				exit_fun(t_variables *var);
void				add_histr_check_syn(char *input, t_variables *var, \
					t_glob **glob);
void				read_input(t_glob **glob, t_variables *var, \
					char **input);

#endif
