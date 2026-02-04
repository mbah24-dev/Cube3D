/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:14:54 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 17:27:17 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    int in_fd = 0;
    int status;
    int ret = 0;
    pid_t pid;

    while (cmds[i])
    {
        if (cmds[i + 1])
        {
            if (pipe(fd) == -1)
                return 1;
        }
        else
        {
            fd[0] = -1;
            fd[1] = -1;
        }

        pid = fork();
        if (pid < 0)
        {
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            if (in_fd != 0)
                close(in_fd);
            return 1;
        }

        if (pid == 0)
        {
            if (in_fd != 0)
            {
                if (dup2(in_fd, 0) == -1)
                    exit(1);
                close(in_fd);
            }
            if (fd[1] != -1)
            {
                if (dup2(fd[1], 1) == -1)
                    exit(1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        else
        {
            if (in_fd != 0)
                close(in_fd);
            if (fd[1] != -1)
                close(fd[1]);
            in_fd = fd[0];
            i++;
        }
    }

    while (wait(&status) > 0)
    {
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
            ret = 1;
    }

    return ret;
}

static int  count_cmds(char **av)
{
    int i = 0;
    int count = 1;

    while (av[i])
    {
        if (av[i][0] == '|' && av[i][1] == '\0')
            count++;
        i++;
    }
    return count;
}

int main(int ac, char **av)
{
    char ***cmds;
    int i = 1;
    int j = 0;
    int k;

    if (ac < 2)
        return 1;

    cmds = (char ***)malloc(sizeof(char **) * (count_cmds(av + 1) + 1));
    if (!cmds)
        return 1;

    while (av[i])
    {
        k = i;
        while (av[k] && !(av[k][0] == '|' && av[k][1] == '\0'))
            k++;

        cmds[j] = (char **)malloc(sizeof(char *) * (k - i + 1));
        if (!cmds[j])
            return 1;

        int x = 0;
        while (i < k)
            cmds[j][x++] = av[i++];

        cmds[j][x] = NULL;
        j++;

        if (av[i] && av[i][0] == '|' && av[i][1] == '\0')
            i++;
    }
    cmds[j] = NULL;

    return picoshell(cmds);
}


