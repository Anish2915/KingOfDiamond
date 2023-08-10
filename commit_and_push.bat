@echo off

echo Automating Git Commit and Push

git add .                             :: Stage all changes
git commit -m "Your message here"     :: Commit changes
git push origin main                  :: Push changes to remote

echo Git commit and push complete
