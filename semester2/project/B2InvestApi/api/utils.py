def check_compatibility_investor_project(investor, project):
    if project.investor is None:
        if investor.capital == project.capital:
            for category in project.categories.all():
                if category in investor.categories.all():
                    return True
    return False


def check_compatibility_expert_project(expert, project):
    if project.capital in expert.capitals.all():
        for category in project.categories.all():
            if category in expert.categories.all():
                return True
    return False
