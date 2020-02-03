import os
import os.path
from shutil import copyfile

# # ABC
# PATH = '/Users/fernando/dev/kth/consensus/src/clone-abc/'
# SOURCE_PATH = '/Users/fernando/dev/abc/bitcoin-abc/src/'

# Core
PATH = '/Users/fernando/dev/kth/consensus/src/clone-core/'
SOURCE_PATH = '/Users/fernando/dev/bitcoin-core/bitcoin/src/'

def replace(kth_files):
    for dp, f in kth_files:
        x = os.path.join(dp, f)

        # print(dp)
        # print(x)
        # print(x[len(PATH):])

        source_file = os.path.join(SOURCE_PATH, x[len(PATH):])   
        print(source_file)
        # print(os.path.isfile(source_file))
        # print(x)

        if os.path.isfile(source_file): 
            os.makedirs(os.path.dirname(x), exist_ok=True)
            # shutil.copy(src_fpath, dest_fpath)            
            copyfile(source_file, x)
        else:
            os.remove(x) 


# kth_files = [os.path.join(dp, f) for dp, dn, filenames in os.walk(PATH) for f in filenames if os.path.splitext(f)[1] == '.txt']
# kth_files = [os.path.join(dp, f) for dp, dn, filenames in os.walk(PATH) for f in filenames]

# kth_files = [(dp, f) for dp, dn, filenames in os.walk(PATH) for f in filenames]
# replace(kth_files)
# # print(kth_files)

# missing_files = [
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/', 'span.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/util/', 'strencodings.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/', 'attributes.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/script/', 'script_metrics.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/script/', 'bitfield.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/util/', 'bitmanip.h'),
#     # ('/Users/fernando/dev/kth/consensus/src/clone-abc/script/', 'bitfield.cpp'),
#     ('/Users/fernando/dev/kth/consensus/src/clone-abc/util/', 'strencodings.cpp'),
# ]
    # ('/Users/fernando/dev/kth/consensus/src/clone-abc/config/', 'bitcoin-config.h'),


missing_files = [
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/', 'span.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/util/', 'strencodings.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/', 'attributes.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/script/', 'script_metrics.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/script/', 'bitfield.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/util/', 'bitmanip.h'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/script/', 'bitfield.cpp'),
    # ('/Users/fernando/dev/kth/consensus/src/clone-core/util/', 'strencodings.cpp'),

    ('/Users/fernando/dev/kth/consensus/src/clone-core/compat/', 'cpuid.h'),
]


# print(missing_files)
replace(missing_files)

# ------------------------------------------------------------------------------------------

