/**
 * _strcmp - compare two strings
 * @string1: string
 * @string2: string
 * Return: 0 if both are same and 1 if they're not
 */
int _stringcmp(const char *string1, const char *string2)
{
	while (*string1 != '\0' && *string2 != '\0' && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);
	return (1);
}
