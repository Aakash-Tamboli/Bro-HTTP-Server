#include<bro_container.h>

bool Container::contains(string keyName)
{
auto iterator=dataSet.find(keyName);
return iterator!=dataSet.end();
}
