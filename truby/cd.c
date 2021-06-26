#include "shell_truby.h"

static char	*ft_strjoin_for_cd(char *s1, char *s2)																		//надо подключить либу и удалить  эти статик функции
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s2);
	s2 = NULL;
	return (new);
}

int use_cd(char **dir, char *root)
{
	char *new_str;

	new_str = NULL;
	if (dir[1] == NULL || dir[1][0] == '~')
	{
		if (dir[1] == NULL || dir[1][1] == '\0')
			chdir(root);
		else
		{
			new_str = ft_substr(dir[1], 1, ft_strlen(dir[1]) - 1);
			new_str = ft_strjoin_for_cd(root, new_str);										//strjoin фришит старый new_str
			chdir(new_str);
			free(new_str);
			new_str = NULL;
		}
	}
	else if (chdir(dir[1]) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), dir[0]);
		// g_status = 1;
	}
	return (0);
}
