/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:01:04 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 14:23:21 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_KEYS_H
# define LINUX_KEYS_H

# define MOUSE_CLICK_RIGHT  -1
# define MOUSE_CLICK_MIDDLE -1
# define MOUSE_CLICK_LEFT   -1
# define MOUSE_WHEEL_DOWN   5
# define MOUSE_WHEEL_UP     4

# define EVENT_KEY_PRESS       2
# define EVENT_KEY_RELEASE     3
# define EVENT_MOUSE_DOWN      4
# define EVENT_MOUSE_UP        5
# define EVENT_MOUSE_MOVE      6
# define EVENT_DESTROY         17

# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363

# define MASK_KEY_PRESS        0
# define MASK_KEY_RELEASE      1
# define MASK_BUTTON_PRESS     2
# define MASK_BUTTON_RELEASE   3
# define MASK_POINTER_MOTION   6
# define MASK_STRUCTURE_NOTIFY 17

#endif
