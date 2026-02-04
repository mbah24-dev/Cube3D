/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:13:48 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 17:47:07 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const av[], char type)
{
    int fd[2];
    pid_t pid;

    if (!file || !av || (type != 'r' && type != 'w'))
        return -1;

    if (pipe(fd) == -1)
        return -1;

    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }

    if (pid == 0)
    {
        if (type == 'r')
        {
            close(fd[0]);
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                exit(1);
        }
        else
        {
            close(fd[1]);
            if (dup2(fd[0], STDIN_FILENO) == -1)
                exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execvp(file, av);
        exit(1);
    }

    if (type == 'r')
    {
        close(fd[1]);
        return fd[0];
    }
    close(fd[0]);
    return fd[1];
}

int main(void)
{
    int fd;
    char buf[1];

    /* ===================== */
    /* TEST 1 : type 'r'     */
    /* ===================== */
    write(1, "=== test r ===\n", 14);

    fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    if (fd == -1)
    {
        write(1, "error\n", 6);
        return 1;
    }
    while (read(fd, buf, 1) > 0)
        write(1, buf, 1);
    close(fd);

    /* ===================== */
    /* TEST 2 : type 'w'     */
    /* ===================== */
    write(1, "\n=== test w ===\n", 15);

    fd = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    if (fd == -1)
    {
        write(1, "error\n", 6);
        return 1;
    }
    write(fd, "hello from ft_popen\n", 21);
    close(fd);

    /* ===================== */
    /* TEST 3 : erreur       */
    /* ===================== */
    write(1, "\n=== test error ===\n", 19);

    fd = ft_popen(NULL, NULL, 'x');
    if (fd == -1)
        write(1, "error OK\n", 9);
    else
        write(1, "error FAIL\n", 11);

    return 0;
}
