def get_state(response):
    count_comma = response.count(",")
    res = 86 - count_comma
    add_ = ''
    for i in range(res):
        add_ += ','
    response = response.replace(']', add_)
    response += ']'
    result = nb_item(response, 'food')
    return result

def nb_item(looked, item):
    cut = looked.split(',')
    count = []
    for i in cut:
        count.append(i.count(item))
    return count
