#include "shell.h"

/**
 * adnod- adds node to head
 * @head: point to head
 * @str: string field of node
 * @numb: index
 *
 * Return: size of list
 */
liststr_t *adnod(liststr_t **head, const char *str, int numb)
{
	liststr_t *nwhead;

	if (!head)
		return (NULL);
	nwhead = malloc(sizeof(liststr_t));
	if (!nwhead)
		return (NULL);
	_memoset((void *)nwhead, 0, sizeof(liststr_t));
	nwhead->numb = numb;
	if (strng)
	{
		nwhead->strng = _strngduplic(strng);
		if (!nwhead->strng)
		{
			free(nwhead);
			return (NULL);
		}
	}
	nwhead->next = *head;
	*head = nwhead;
	return (nwhead);
}

/**
 * adnodend- add  node at tail
 * @head: point to head
 * @strng: the string
 * @numb: index
 *
 * Return: size of list
 */
liststr_t *adnodend(liststr_t **head, const char *strng, int numb)
{
	liststr_t *nwnode, *node;

	if (!head)
		return (NULL);

	node = *head;
	nwnode = malloc(sizeof(liststr_t));
	if (!nwnode)
		return (NULL);
	_memoset((void *)nwnode, 0, sizeof(liststr_t));
	nwnode->numb = numb;
	if (strng)
	{
		nwnode->strng = _strngduplic(strng);
		if (!nwnode->strng)
		{
			free(nwnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nwnode;
	}
	else
		*head = nwnode;
	return (nwnode);
}


/**
 * prntlststring- prints only the string  elements of a linked list
 * @headarr: pointer point to the head node
 *
 * Return: the size
 */
size_t prntlststring(const liststr_t *headarr)
{
	size_t countr = 0;

	while (headarr)
	{
		_puts(headarr->strng ? headarr->strng : "(nil)");
		_puts("\n");
		headarr = headarr->next;
		countr++;
	}
	return (countr);
}

/**
 * delnod- delete node
 * @head: point to head
 * @indx: index of the node to delete
 *
 * Return: 1 on success, 0 on otherwise
 */
int delnod(liststr_t **head, unsigned int indx)
{
	liststr_t *pnode, *previous_node;
	unsigned int countr = 0;

	if (!head || !*head)
		return (0);

	if (!indx)
	{
		pnode = *head;
		*head = (*head)->next;
		free(pnode->strng);
		free(pnode);
		return (1);
	}
	pnode = *head;
	while (pnode)
	{
		if (countr == indx)
		{
			previous_node->next = pnode->next;
			free(pnode->strng);
			free(pnode);
			return (1);
		}
		countr++;
		previous_node = pnode;
		pnode = pnode->next;
	}
	return (0);
}

/**
 * frlst- frees nodes on the linked list
 * @phead: address points to the first node at the head
 *
 * Return: void
 */
void frlst(liststr_t **phead)
{
	liststr_t *pnode, *nxtnode, *head;

	if (!phead || !*phead)
		return;
	head = *phead;
	pnode = head;
	while (pnode)
	{
		nxtnode = pnode->next;
		free(pnode->strng);
		free(pnode);
		pnode = nxtnode;
	}
	*phead = NULL;
}
