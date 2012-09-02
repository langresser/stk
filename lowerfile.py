import os
def lowerfile():
  for root,dirs,files in os.walk('data'):
    for file in files:
      path = root + '/' + file;
      if path.find('.svn') != -1:
        continue;

      if path.find('.DS_Store') != -1:
        continue;

      os.rename(path, path.lower());
      print(path.lower());

lowerfile();