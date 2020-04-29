# Contributors Guide

Hii developers, thanks for your interest in contributing to **MinimalOS**, but there are
a few thinks you need to be aware of as a contributor or a potential contributor to this
project.

Ignorance of these guidelines may cause rejection and premature closure of your pull requests.

### Steps to become a contributor

1. Fork this repository in _github_ so that you have a personal copy of the project code.

2. Decide what you want to work on. The best place to look for something to work is the issues page.
	* Navigate to the Issues page.
	* Search something you want to work on.
	* If you find an issue with the label `good first issue`. You may want to try that before diving into the codebase.

3. Ask to be assigned to an issue in the comment sections.

4. Once assigned, you can start working on your copy of this project.

If you don't like any of the issues we currently have and have an idea for a feature to
implement or found a new bug you want to solve, create an issue exlaining your idea or bug
and do comment below that you would like to work on it.

And please don't hesitate in your communications, which must obviously follow our code of
conduct, because _it's us who want your help_.

### Git Commits

Please do maintain a uniform style for commit messages and descriptions.

The commit messages should be in the format :

[fix|feature|doc]: [subsystem or module]: "A short description of the [fix|feature|doc]"

Note: Please try to make your commit message as short as possible.

The commit descriptions should describe the __why__ of the changes you have made.
And following that a list of files you have modified or added and a little technical description
of the change.

You should remember the following points while commiting to the codebase.
* The changes in a commit must form a logical unit.
* We don't want unnecessary and redundant commits. E.g. reverting a change you made in the next commits.
* Keep the number of commits to a minimum.
* We may ask you to change the commit messages and descriptions if we find them sub-standard.

### Issuing a pull request

Please do ensure that you have a clean git history, before making any pull requests, by following
commit best practices.
And you should always add new changes to the codebase on top of the latest git history.
You can do so with the help of `git rebase` command.

Now you are all set to contribute to __MinimalOS__.
