#include "../shell.h"

int     check_for_dollar(char symbol)
{
    int res;

    res = 1;
    if (symbol == '_')
        res = 0;
    if (symbol >= 'a' && symbol <= 'z')
        res = 0;
    if (symbol >= 'A' && symbol <= 'Z')
        res = 0;
    if (symbol >= '0' && symbol <= '9')
        res = 0;
    return (res);
}

int    dollar_make(t_all *tmp, int i, char **env)
{
    t_dollar    *d;

    d = (t_dollar *)malloc(sizeof(t_dollar));
    d->i_str = i - 1;
    d->remember = i - 1;
    d->count = 0;
    while (check_for_dollar(tmp->str[++(d->i_str)]) == 0)
        d->count++;
    tmp->temporary_array = (char *)malloc(sizeof(char) * (d->count + 2));
    tmp->temporary_array[d->count] = '=';
    tmp->temporary_array[d->count + 1] = '\0';
    d->i_str = 0;
    while (d->i_str < d->count)
    {
        tmp->temporary_array[d->i_str] = tmp->str[i];
        d->i_str++;
        i++;
    }
    d->count++;
    search(tmp, env, d);
    free(tmp->temporary_array);
    free(d);
    return (d->remember);
}

void    search(t_all *tmp, char **env, t_dollar *d)
{
    d->i_env = 0;
    while (env[d->i_env] != NULL)
    {
        if(ft_strncmp(env[d->i_env], tmp->temporary_array, d->count) == 0)
        {
            create_new_str(tmp, env, d);
            break ;
        }
        d->i_env++;
    }
}

void    create_new_str(t_all *tmp, char **env, t_dollar *d)
{
    int temp;

    d->j_env = 0;
    d->count = ft_strlen(tmp->str);
    d->count = d->count - ft_strlen(tmp->temporary_array);
    temp = ft_strlen(env[d->i_env]) - ft_strlen(tmp->temporary_array);
    d->count = d->count + temp;
    while (env[d->i_env][d->j_env] != '=')
        d->j_env++;
    d->j_env++;
    create_array(tmp, env, d);
}

void    create_array(t_all *tmp, char **env, t_dollar *d)
{
    char *new_str;

    d->i_new = 0;
    d->i_str = 0;
    new_str = (char *)malloc(sizeof(char) * d->count + 1);
    new_str[d->count] = '\0';
    while (d->i_str < d->remember && d->i_new < d->count)
    {
        new_str[d->i_new] = tmp->str[d->i_str];
        d->i_new++;
        d->i_str++;
    }
    while (env[d->i_env][d->j_env] != '\0' && d->i_new < d->count)
    {
        new_str[d->i_new] = env[d->i_env][d->j_env];
        d->i_new++;
        d->j_env++;
    }
    d->i_str++;
    while (check_for_dollar(tmp->str[d->i_str]) == 0)
        d->i_str++;
    while (tmp->str[d->i_str] != '\0' && d->i_new < d->count)
    {
        new_str[d->i_new] = tmp->str[d->i_str];
        d->i_new++;
        d->i_str++;
    }
    free(tmp->str);
    tmp->str = new_str;
}
