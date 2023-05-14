import csvparser
from pprint import pprint


def transform_age(cell: str):
    age = int(cell)
    return age + 5


def transform_city(cell: str):
    return cell.upper()


transforms = [None, transform_age, transform_city]
cities = csvparser.parse_csv("cities.csv", trim=True, transforms=transforms)
pprint(cities)

