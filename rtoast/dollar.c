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

void    dollar_make(t_all *tmp, int i, char **env)
{
    int     j;
    int     count;

    j = i;
    count = 0;
    while (check_for_dollar(tmp->str[j]) == 0)
    {
        j++;
        count++;
    }
    tmp->temporary_array = (char *)malloc(sizeof(char) * (count + 2));
    tmp->temporary_array[count] = '=';
    tmp->temporary_array[count + 1] = '\0';
    j = 0;
    while (j < count)
    {
        tmp->temporary_array[j] = tmp->str[i];
        j++;
        i++;
    }
    search(tmp, env, count + 1);
    free(tmp->temporary_array);
}

void    search(t_all *tmp, char **env, int count)
{
    int     i;
    int     j;
    int     symbol;

    i = 0;
    j = 0;
    symbol = 0;
    while (env[i] != NULL)
    {
        if(ft_strncmp(env[i], tmp->temporary_array, count) == 0)
        {
            create_new_str(tmp, env, i);
            break ;
        }
        i++;
    }
}

void    create_new_str(t_all *tmp, char **env, int i)
{
    int count;
    int t_c;
    int e_c;

    e_c = 0;
    count = ft_strlen(tmp->str);
    count = count - ft_strlen(tmp->temporary_array);
    t_c = ft_strlen(env[i]) - ft_strlen(tmp->temporary_array);
    count = count + t_c;
    while (env[i][e_c] != '=')
        e_c++;
    create_array(tmp, env, i, count, ++e_c);
}

void    create_array(t_all *tmp, char **env, int i, int count, int c)
{
    char *new_str;
    int j;
    int i_s;

    j = 0;
    i_s = 0;
    new_str = (char *)malloc(sizeof(char) * count + 1);
    new_str[count] = '\0';
    while (tmp->str[i_s] != '$' && j < count)
    {
        new_str[j] = tmp->str[i_s];
        j++;
        i_s++;
    }
    while (env[i][c] != '\0' && j < count)
    {
        new_str[j] = env[i][c];
        j++;
        c++;
    }
    while (check_for_dollar(tmp->str[i_s]) == 0)
        i_s++;
    while (tmp->str[i_s] != '\0' && j < count)
    {
        new_str[j] = tmp->str[i_s];
        j++;
        i_s++;
    }
    free(tmp->str);
    tmp->str = new_str;
}
