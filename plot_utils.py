import numpy as np
from matplotlib import pyplot

def plot_setup(plot_molecules,par0list,par1list,params):
     pyplot.ion()
     fig,axes=pyplot.subplots(len(plot_molecules), 1,sharex=True) #n rows,  1 column
     if len(params):
          minp0=np.min(par0list)
          maxp0=np.max(par0list)
          if minp0<=0:
               minp0=np.sort(par0list)[1]
          if len(par0list)>2 and maxp0/minp0>99:
               rinc=1/(np.log10(maxp0)-np.log10(minp0))
               scale0='log'
          else:
               rinc=1/(maxp0-minp0)
               scale0='lin'
          if len(params)>1:
               minp1=np.min(par1list)
               maxp1=np.max(par1list)
               if minp1<=0:
                    minp1=np.sort(par1list)[1]
               if len(par1list)>2 and maxp1/minp1>99:  #large range - log color scale
                    binc=1/(np.log10(maxp1)-np.log10(minp1))
                    scale1='log'
               else:               #small range - linear color scale
                    binc=1/(maxp1-minp1)
                    scale1='lin'
          else:
               binc=rinc
               scale1=scale0
               minp1=minp0
          col_inc=(rinc,binc)
          scale=(scale0,scale1)
          minpar=(minp0,minp1)
     else:
          col_inc=(0.5,0.5)
          scale=('lin','lin')
          minpar=(0,0)
     return fig,axes,col_inc,scale,minpar

def plottrace(plotmol,time,plotarray,parval,axes,fig,colinc,scale,minpar):
     if np.size(parval)==1:
          if scale[0]=='lin':
               p0=p1=parval-minpar[0]
          else:
               p0=p1=np.log10(parval)-np.log10(minpar[0])
     if np.size(parval)>1:
          if scale[0]=='log':
               p0=np.log10(parval[0])-np.log10(minpar[0])
          else:
               p0=parval[0]-minpar[0]
          if scale[1]=='log':
               p1=np.log10(parval[1])-np.log10(minpar[1])
          else:
               p1=parval[1]-minpar[1]
     for imol,mol in enumerate(plotmol):
          if imol==0:
               axes[imol].plot(time,plotarray[:,imol],label=parval,color=(p0*colinc[0],0,p1*colinc[1]))
          else:
               axes[imol].plot(time,plotarray[:,imol],color=(p0*colinc[0],0,p1*colinc[1]))
          axes[imol].set_ylabel(mol)#+' (nM)')
          axes[imol].legend(fontsize=8, loc='best')
     axes[imol].set_xlabel('Time (sec)')
     fig.canvas.draw()
     return

def plotss(plot_mol,xparval,ss):
    fig,axes=pyplot.subplots(len(plot_mol), 1,sharex=True)
    for imol,mol in enumerate(plot_mol):
        axes[imol].plot(xparval,ss[:,imol],'o',label=mol)
        axes[imol].set_ylabel('nM')
        if max(xparval)/min(xparval)>100:
            axes[imol].set_xscale("log")
        axes[imol].legend(fontsize=8, loc='best')
    fig.canvas.draw()
    return

#The files are sorted on the parameters, assumes no hyphens in root filename
def file_tuple(fnames,params):
     ftuple=[]
     par0list=[]
     par1list=[]
     for fname in fnames:
            parts=fname.split('-')
            parval0=float(parts[1].split(params[0])[1])
            if (parval0 not in par0list):
                 par0list.append(parval0)
            print fname,par0list
            if len(params)>1:
                    parval1=float(parts[2].split(params[1])[1])
                    ftuple.append((fname,(parval0,parval1)))
                    if (parval1 not in par1list):
                         par1list.append(parval1)
            else:
                    ftuple.append((fname,parval0))
     return ftuple,par0list,par1list

