import numpy as np

def header_parse(header,maxvols,prninfo):
    #Define some substrings used in reading header
    underscore='_'
    dot='.'
    #
    #number of voxels in the file
    volnum=np.zeros(maxvols)
    regionID=list()
    structType=list()
    molecules=list()
    #
    volnames=header.split()
    for i in range(maxvols):
        #print "volname",volnames[i+1]
        voxel_text=volnames[i+1].split(underscore)
        #voxel number is 2nd "phrase"
        volnum[i]=int(voxel_text[1])
        if i==0:
            minvolnum=int(volnum[0])
            print "min vox num", minvolnum,"max vox num", maxvols
        #if output of only part of morphology, need to reduce maxvols
        if (i>0 and volnum[i]==volnum[0]):
            maxvols=int(volnum[i-1]-minvolnum+1)
            print "*******new max", maxvols
            #need to exit loop
        else:
            dotyn=voxel_text[2].find(dot)
            if dotyn==-1:
                #region ID, such as dendrite, is 3d "phrase" if not spine
                #for shorter heading, only use first 3 char of region ID
                regionID.append(voxel_text[2][0:4])
            else:
                regionID.append(voxel_text[2].split(dot)[0])
            #sm vs cyt is 4th "phrase"
            structType.append(voxel_text[3][0:3])
    volnums=np.resize(volnum,maxvols)
    #These two lines not needed once loop exited
    regionID=np.resize(regionID,maxvols)
    structType=np.resize(structType,maxvols)
    if prninfo:
        print "in hparse: voxels", volnums
        print "   regionID", np.size(regionID),regionID
        print "   structures", np.size(structType),structType
    #
    #Now determine the molecules in the file - last characters of volume string
    #skip all[0] which has time, increment by maxvols to find vol0 of each molecule
    for i,j in enumerate(range(1,len(volnames),maxvols)):
        molecules.append(volnames[j].split(underscore)[-1])
        if prninfo:
            print j, volnames[j],molecules[i]
    return regionID,structType,molecules,volnums,maxvols

def read_mesh(meshname):
    volcol=13
    #the x and y data can be used to create spatial averages over the dendrite
    #sum of volumes within a region will be used for calculating mean concentration
    meshdata=np.loadtxt(meshname,skiprows=1)
    if np.shape(meshdata)[0]==np.size(meshdata):
        print 'mesh file:', meshdata
        volume=meshdata[volcol]
        xloc=meshdata[1]
        yloc=meshdata[2]
        depth=meshdata[volcol+1]
        SurfaceLayer=np.abs(yloc-meshdata[8])
        maxvols=1
        TotVol=volume
    else:
        print '1st mesh file row:', meshdata[0,:]
        volume=meshdata[:,volcol]
        depth=meshdata[:,volcol+1]
        maxvols=len(volume)
        xloc=meshdata[:,1]
        yloc=meshdata[:,2]
        SurfaceLayer=np.abs(yloc-meshdata[:,8])
        TotVol=0
        for k in range(maxvols):
            TotVol+=volume[k]
    print "TotVol:", TotVol, "depth", depth, "deltaY", SurfaceLayer
    return maxvols,volume,xloc,yloc,TotVol,SurfaceLayer

def region_volume(List,Vox,volume,prnvox):
    #This volume is in units of cubic microns, multiply by 1e-15 to convert to Liters
    print "\nFOR region avg: j,regionvox,vol:",
    region_volume=np.zeros(len(List))
    for j in range(len(List)):
        for k in Vox[j]:
            region_volume[j]+=volume[k] 
        if prnvox:
            print "\n ", j, List[j],Vox[j],region_volume[j]
        else:
            print "not printed"
    return region_volume

def subvol_list(structType,regionID,volnum,fake):
    yes=1
    no=0
    #all voxels should be read in now with labels
    #extract number of unique regions (e.g. dendrite, or sa1[0]), 
    #and create list of subvolumes which contribute to that region
    regionList=list()
    regionVox=list()
    regionCol=list()
    regionStructList=list()
    regionStructVox=list()
    regionStructCol=list()

    for i in range(len(volnum)):
        if (structType[i] != fake):
            unique=yes
            regionStruct=regionID[i]+structType[i]
            uniqueStruct=yes
            #print "vol,regionStruct",i,regionStruct,"num regions:", len(regionList)
            #first construct list of region specific voxels
            j=0
            while ((unique==yes) and (j<len(regionList))):
                if regionID[i]==regionList[j]:
                    regionVox[j].append(volnum[i])
                    regionCol[j].append(i)
                    unique=no
                #endif
                j+=1
            #endwhile
            if (unique==yes):
                regionList.append(regionID[i])
                regionVox.append([])
                regionCol.append([])
                regionVox[len(regionList)-1].append(volnum[i])
                regionCol[len(regionList)-1].append(i)
            #endif
            #second construct list of region and structure specific voxels.
            j=0
            while ((uniqueStruct==yes) and (j<len(regionStructList))):
                if (regionStruct==regionStructList[j]):
                    regionStructVox[j].append(volnum[i])
                    regionStructCol[j].append(i)
                    uniqueStruct=no
                #endif
                j+=1
            #endwhile
            if (uniqueStruct==yes):
                regionStructList.append(regionStruct)
                regionStructVox.append([])
                regionStructCol.append([])
                regionStructVox[len(regionStructList)-1].append(volnum[i])
                regionStructCol[len(regionStructList)-1].append(i)
            #endif
    #end for i
    return regionList,regionVox,regionCol,regionStructList,regionStructVox,regionStructCol

#Not yet debugged
def spatial_average(xloc,yloc,bins,regionID,structType,volnum):
    binmin=np.zeros(bins+1)
    binvoxels=[]
    bincolumns=[]
    xdim=max(xloc)-min(xloc)
    ydim=max(yloc)-min(yloc)

    #First, create the bins
    #xdim is larger:
    if (xdim >= ydim):
        bininc=xdim/bins
        minloc=min(xloc)
        maxloc=max(xloc)
        loc=xloc
        spaceheader='#time, x='
    #ydim is larger:
    else:
        bininc=ydim/bins
        minloc=min(yloc)
        maxloc=max(yloc)
        loc=yloc
        spaceheader='#time, y='
#now that assignmenst are made, determine bins the same for x or y direciton
    for j in range(bins):
        binmin[j]=minloc+j*bininc
        binvoxels.append([])
        bincolumns.append([])
    binmin[bins]=maxloc+bininc/bins
     
    #Now assign voxels to bins, either by x or y location
    print "binmin: ",binmin[:]
    print "regions=", len(regionID), "structures=", len(structType), "meshfile=", len(volume), "volnums=", len(volnum)
    for k in range(len(volnum)):
        if (regionID[k]==dend):
            j=0
            assigned=no
            while ((j < bins) and (assigned==no)):
                if ((loc[k]>=binmin[j]) and (loc[k] < binmin[j+1])):
                    binvoxels[j].append(volnum[k])
                    bincolumns[j].append(k)
                    assigned=yes
                j=j+1
            
    #now calculate volume for these spatial bins
    SpatialVol=np.zeros(bins)
    print "\nFOR spatial average: j, vol, binvoxels, bincolums:"
    for j in range(bins):
        for k in binvoxels[j]:
            SpatialVol[j]+=volume[k]
        if (prnvox==1):
            print j, SpatialVol[j], binvoxels[j], bincolumns[j]
        else:
            print "not printed"

    for j in range(bins):
        spaceheader=spaceheader+' '+str(format(binmin[j],'.1f'))+'-'+str(format(binmin[j]+bininc,'.1f'))
    print 'Space header:', spaceheader
    return


 
