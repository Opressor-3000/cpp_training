# Branches Workflow

This document outlines the Git branching workflow for the repository. 
It aims to provide clear guidelines for managing branches effectively, 
ensuring a smooth development process, and facilitating collaboration 
within the team.

## Workflow

Create a new branch from the develop branch for any new feature, bugfix, 
or enhancement. Use descriptive names for branches 
(e.g., feature/login-page, bugfix/fix-header).

Work on the branch until the feature or fix is complete. Keep commits focused and organized. Use meaningful commit messages to describe each change.

Push your branch to the remote repository to share your progress and make it accessible for team collaboration<br>:

```
git push origin <branch-name>
```


Open a Pull Request (PR) once your work is finished. 
A PR is a request to merge your changes into the appropriate 
base branch (usually develop or main). Include a clear 
description of what your PR does and any relevant context.

Review and testing: Once the PR is created, team members will 
review the code and run any necessary tests. 
Address feedback and make changes as needed.

Merge the PR: After approval and successful testing, the PR will be 
merged into the target branch (develop for new features, 
main for hotfixes or releases). Ensure that the branch is up to 
date with the latest changes before merging.

Delete the branch: After merging, delete the branch both 
locally and remotely to keep the repository clean.<br>

```
git branch -d <branch-name>           
git push origin --delete <branch-name> 
```

By following this workflow, we ensure that our development 
process remains efficient, organized, and that we maintain high-quality code.

Don't forget to read [README.md](./README.md)