/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic_utils
*/

#include "amber_logic.h"

int clamp(int min, int current, int max)
{
  while (current < min || current > max) {
    if (current < min)
      current = max - (ABS(current) - ABS(min));
    if (current > max)
      current = min + (ABS(current) - max);
  }
  return current;
}

int real_clamp(int min, int current, int max)
{
  if (current < min)
    return min;
  if (current > max)
    return max;
  return current;
}

void send_client_message(amber_client_t *client, const char *message)
{
    dprintf(client->_tcp._fd, "%s\n", message);
}
