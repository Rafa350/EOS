//
#ifndef __XC_ASM_H
#define __XC_ASM_H

#if defined(__MEC1404__)
#  include <proc/pmec1404.h>
#elif defined(__MEC1406__)
#  include <proc/pmec1406.h>
#elif defined(__MEC1408__)
#  include <proc/pmec1408.h>
#elif defined(__MEC1418__)
#  include <proc/pmec1418.h>
#elif defined(__MGC3430__)
#  include <proc/pmgc3430.h>
#elif defined(__MGC3431__)
#  include <proc/pmgc3431.h>
#elif defined(__MGC3450__)
#  include <proc/pmgc3450.h>
#elif defined(__MGC3451__)
#  include <proc/pmgc3451.h>
#elif defined(__32MM0016GPL020__)
#  include <proc/p32mm0016gpl020.h>
#elif defined(__32MM0016GPL028__)
#  include <proc/p32mm0016gpl028.h>
#elif defined(__32MM0016GPL036__)
#  include <proc/p32mm0016gpl036.h>
#elif defined(__32MM0032GPL020__)
#  include <proc/p32mm0032gpl020.h>
#elif defined(__32MM0032GPL028__)
#  include <proc/p32mm0032gpl028.h>
#elif defined(__32MM0032GPL036__)
#  include <proc/p32mm0032gpl036.h>
#elif defined(__32MM0064GPL020__)
#  include <proc/p32mm0064gpl020.h>
#elif defined(__32MM0064GPL028__)
#  include <proc/p32mm0064gpl028.h>
#elif defined(__32MM0064GPL036__)
#  include <proc/p32mm0064gpl036.h>
#elif defined(__32MX110F016B__)
#  include <proc/p32mx110f016b.h>
#elif defined(__32MX110F016C__)
#  include <proc/p32mx110f016c.h>
#elif defined(__32MX110F016D__)
#  include <proc/p32mx110f016d.h>
#elif defined(__32MX120F032B__)
#  include <proc/p32mx120f032b.h>
#elif defined(__32MX120F032C__)
#  include <proc/p32mx120f032c.h>
#elif defined(__32MX120F032D__)
#  include <proc/p32mx120f032d.h>
#elif defined(__32MX120F064H__)
#  include <proc/p32mx120f064h.h>
#elif defined(__32MX130F064B__)
#  include <proc/p32mx130f064b.h>
#elif defined(__32MX130F064C__)
#  include <proc/p32mx130f064c.h>
#elif defined(__32MX130F064D__)
#  include <proc/p32mx130f064d.h>
#elif defined(__32MX130F128H__)
#  include <proc/p32mx130f128h.h>
#elif defined(__32MX130F128L__)
#  include <proc/p32mx130f128l.h>
#elif defined(__32MX130F256B__)
#  include <proc/p32mx130f256b.h>
#elif defined(__32MX130F256D__)
#  include <proc/p32mx130f256d.h>
#elif defined(__32MX150F128B__)
#  include <proc/p32mx150f128b.h>
#elif defined(__32MX150F128C__)
#  include <proc/p32mx150f128c.h>
#elif defined(__32MX150F128D__)
#  include <proc/p32mx150f128d.h>
#elif defined(__32MX150F256H__)
#  include <proc/p32mx150f256h.h>
#elif defined(__32MX150F256L__)
#  include <proc/p32mx150f256l.h>
#elif defined(__32MX151F128E__)
#  include <proc/p32mx151f128e.h>
#elif defined(__32MX151F128H__)
#  include <proc/p32mx151f128h.h>
#elif defined(__32MX170F256B__)
#  include <proc/p32mx170f256b.h>
#elif defined(__32MX170F256D__)
#  include <proc/p32mx170f256d.h>
#elif defined(__32MX170F512H__)
#  include <proc/p32mx170f512h.h>
#elif defined(__32MX170F512L__)
#  include <proc/p32mx170f512l.h>
#elif defined(__32MX210F016B__)
#  include <proc/p32mx210f016b.h>
#elif defined(__32MX210F016C__)
#  include <proc/p32mx210f016c.h>
#elif defined(__32MX210F016D__)
#  include <proc/p32mx210f016d.h>
#elif defined(__32MX220F032B__)
#  include <proc/p32mx220f032b.h>
#elif defined(__32MX220F032C__)
#  include <proc/p32mx220f032c.h>
#elif defined(__32MX220F032D__)
#  include <proc/p32mx220f032d.h>
#elif defined(__32MX230F064B__)
#  include <proc/p32mx230f064b.h>
#elif defined(__32MX230F064C__)
#  include <proc/p32mx230f064c.h>
#elif defined(__32MX230F064D__)
#  include <proc/p32mx230f064d.h>
#elif defined(__32MX230F128H__)
#  include <proc/p32mx230f128h.h>
#elif defined(__32MX230F128L__)
#  include <proc/p32mx230f128l.h>
#elif defined(__32MX230F256B__)
#  include <proc/p32mx230f256b.h>
#elif defined(__32MX230F256D__)
#  include <proc/p32mx230f256d.h>
#elif defined(__32MX250F128B__)
#  include <proc/p32mx250f128b.h>
#elif defined(__32MX250F128C__)
#  include <proc/p32mx250f128c.h>
#elif defined(__32MX250F128D__)
#  include <proc/p32mx250f128d.h>
#elif defined(__32MX250F256H__)
#  include <proc/p32mx250f256h.h>
#elif defined(__32MX250F256L__)
#  include <proc/p32mx250f256l.h>
#elif defined(__32MX251F128E__)
#  include <proc/p32mx251f128e.h>
#elif defined(__32MX251F128H__)
#  include <proc/p32mx251f128h.h>
#elif defined(__32MX270F256B__)
#  include <proc/p32mx270f256b.h>
#elif defined(__32MX270F256D__)
#  include <proc/p32mx270f256d.h>
#elif defined(__32MX270F512H__)
#  include <proc/p32mx270f512h.h>
#elif defined(__32MX270F512L__)
#  include <proc/p32mx270f512l.h>
#elif defined(__32MX320F032H__)
#  include <proc/p32mx320f032h.h>
#elif defined(__32MX320F064H__)
#  include <proc/p32mx320f064h.h>
#elif defined(__32MX320F128H__)
#  include <proc/p32mx320f128h.h>
#elif defined(__32MX320F128L__)
#  include <proc/p32mx320f128l.h>
#elif defined(__32MX330F064H__)
#  include <proc/p32mx330f064h.h>
#elif defined(__32MX330F064L__)
#  include <proc/p32mx330f064l.h>
#elif defined(__32MX340F128H__)
#  include <proc/p32mx340f128h.h>
#elif defined(__32MX340F128L__)
#  include <proc/p32mx340f128l.h>
#elif defined(__32MX340F256H__)
#  include <proc/p32mx340f256h.h>
#elif defined(__32MX340F512H__)
#  include <proc/p32mx340f512h.h>
#elif defined(__32MX350F128H__)
#  include <proc/p32mx350f128h.h>
#elif defined(__32MX350F128L__)
#  include <proc/p32mx350f128l.h>
#elif defined(__32MX350F256H__)
#  include <proc/p32mx350f256h.h>
#elif defined(__32MX350F256L__)
#  include <proc/p32mx350f256l.h>
#elif defined(__32MX360F256L__)
#  include <proc/p32mx360f256l.h>
#elif defined(__32MX360F512L__)
#  include <proc/p32mx360f512l.h>
#elif defined(__32MX370F512H__)
#  include <proc/p32mx370f512h.h>
#elif defined(__32MX370F512L__)
#  include <proc/p32mx370f512l.h>
#elif defined(__32MX420F032H__)
#  include <proc/p32mx420f032h.h>
#elif defined(__32MX430F064H__)
#  include <proc/p32mx430f064h.h>
#elif defined(__32MX430F064L__)
#  include <proc/p32mx430f064l.h>
#elif defined(__32MX440F128H__)
#  include <proc/p32mx440f128h.h>
#elif defined(__32MX440F128L__)
#  include <proc/p32mx440f128l.h>
#elif defined(__32MX440F256H__)
#  include <proc/p32mx440f256h.h>
#elif defined(__32MX440F512H__)
#  include <proc/p32mx440f512h.h>
#elif defined(__32MX450F128H__)
#  include <proc/p32mx450f128h.h>
#elif defined(__32MX450F128L__)
#  include <proc/p32mx450f128l.h>
#elif defined(__32MX450F256H__)
#  include <proc/p32mx450f256h.h>
#elif defined(__32MX450F256L__)
#  include <proc/p32mx450f256l.h>
#elif defined(__32MX460F256L__)
#  include <proc/p32mx460f256l.h>
#elif defined(__32MX460F512L__)
#  include <proc/p32mx460f512l.h>
#elif defined(__32MX470F512H__)
#  include <proc/p32mx470f512h.h>
#elif defined(__32MX470F512L__)
#  include <proc/p32mx470f512l.h>
#elif defined(__32MX530F128H__)
#  include <proc/p32mx530f128h.h>
#elif defined(__32MX530F128L__)
#  include <proc/p32mx530f128l.h>
#elif defined(__32MX534F064H__)
#  include <proc/p32mx534f064h.h>
#elif defined(__32MX534F064L__)
#  include <proc/p32mx534f064l.h>
#elif defined(__32MX550F256H__)
#  include <proc/p32mx550f256h.h>
#elif defined(__32MX550F256L__)
#  include <proc/p32mx550f256l.h>
#elif defined(__32MX564F064H__)
#  include <proc/p32mx564f064h.h>
#elif defined(__32MX564F064L__)
#  include <proc/p32mx564f064l.h>
#elif defined(__32MX564F128H__)
#  include <proc/p32mx564f128h.h>
#elif defined(__32MX564F128L__)
#  include <proc/p32mx564f128l.h>
#elif defined(__32MX570F512H__)
#  include <proc/p32mx570f512h.h>
#elif defined(__32MX570F512L__)
#  include <proc/p32mx570f512l.h>
#elif defined(__32MX575F256H__)
#  include <proc/p32mx575f256h.h>
#elif defined(__32MX575F256L__)
#  include <proc/p32mx575f256l.h>
#elif defined(__32MX575F512H__)
#  include <proc/p32mx575f512h.h>
#elif defined(__32MX575F512L__)
#  include <proc/p32mx575f512l.h>
#elif defined(__32MX664F064H__)
#  include <proc/p32mx664f064h.h>
#elif defined(__32MX664F064L__)
#  include <proc/p32mx664f064l.h>
#elif defined(__32MX664F128H__)
#  include <proc/p32mx664f128h.h>
#elif defined(__32MX664F128L__)
#  include <proc/p32mx664f128l.h>
#elif defined(__32MX675F256H__)
#  include <proc/p32mx675f256h.h>
#elif defined(__32MX675F256L__)
#  include <proc/p32mx675f256l.h>
#elif defined(__32MX675F512H__)
#  include <proc/p32mx675f512h.h>
#elif defined(__32MX675F512L__)
#  include <proc/p32mx675f512l.h>
#elif defined(__32MX695F512H__)
#  include <proc/p32mx695f512h.h>
#elif defined(__32MX695F512L__)
#  include <proc/p32mx695f512l.h>
#elif defined(__32MX764F128H__)
#  include <proc/p32mx764f128h.h>
#elif defined(__32MX764F128L__)
#  include <proc/p32mx764f128l.h>
#elif defined(__32MX775F256H__)
#  include <proc/p32mx775f256h.h>
#elif defined(__32MX775F256L__)
#  include <proc/p32mx775f256l.h>
#elif defined(__32MX775F512H__)
#  include <proc/p32mx775f512h.h>
#elif defined(__32MX775F512L__)
#  include <proc/p32mx775f512l.h>
#elif defined(__32MX795F512H__)
#  include <proc/p32mx795f512h.h>
#elif defined(__32MX795F512L__)
#  include <proc/p32mx795f512l.h>
#elif defined(__32MZ0512EFE064__)
#  include <proc/p32mz0512efe064.h>
#elif defined(__32MZ0512EFE100__)
#  include <proc/p32mz0512efe100.h>
#elif defined(__32MZ0512EFE124__)
#  include <proc/p32mz0512efe124.h>
#elif defined(__32MZ0512EFE144__)
#  include <proc/p32mz0512efe144.h>
#elif defined(__32MZ0512EFF064__)
#  include <proc/p32mz0512eff064.h>
#elif defined(__32MZ0512EFF100__)
#  include <proc/p32mz0512eff100.h>
#elif defined(__32MZ0512EFF124__)
#  include <proc/p32mz0512eff124.h>
#elif defined(__32MZ0512EFF144__)
#  include <proc/p32mz0512eff144.h>
#elif defined(__32MZ0512EFK064__)
#  include <proc/p32mz0512efk064.h>
#elif defined(__32MZ0512EFK100__)
#  include <proc/p32mz0512efk100.h>
#elif defined(__32MZ0512EFK124__)
#  include <proc/p32mz0512efk124.h>
#elif defined(__32MZ0512EFK144__)
#  include <proc/p32mz0512efk144.h>
#elif defined(__32MZ1024ECG064__)
#  include <proc/p32mz1024ecg064.h>
#elif defined(__32MZ1024ECG100__)
#  include <proc/p32mz1024ecg100.h>
#elif defined(__32MZ1024ECG124__)
#  include <proc/p32mz1024ecg124.h>
#elif defined(__32MZ1024ECG144__)
#  include <proc/p32mz1024ecg144.h>
#elif defined(__32MZ1024ECH064__)
#  include <proc/p32mz1024ech064.h>
#elif defined(__32MZ1024ECH100__)
#  include <proc/p32mz1024ech100.h>
#elif defined(__32MZ1024ECH124__)
#  include <proc/p32mz1024ech124.h>
#elif defined(__32MZ1024ECH144__)
#  include <proc/p32mz1024ech144.h>
#elif defined(__32MZ1024ECM064__)
#  include <proc/p32mz1024ecm064.h>
#elif defined(__32MZ1024ECM100__)
#  include <proc/p32mz1024ecm100.h>
#elif defined(__32MZ1024ECM124__)
#  include <proc/p32mz1024ecm124.h>
#elif defined(__32MZ1024ECM144__)
#  include <proc/p32mz1024ecm144.h>
#elif defined(__32MZ1024EFE064__)
#  include <proc/p32mz1024efe064.h>
#elif defined(__32MZ1024EFE100__)
#  include <proc/p32mz1024efe100.h>
#elif defined(__32MZ1024EFE124__)
#  include <proc/p32mz1024efe124.h>
#elif defined(__32MZ1024EFE144__)
#  include <proc/p32mz1024efe144.h>
#elif defined(__32MZ1024EFF064__)
#  include <proc/p32mz1024eff064.h>
#elif defined(__32MZ1024EFF100__)
#  include <proc/p32mz1024eff100.h>
#elif defined(__32MZ1024EFF124__)
#  include <proc/p32mz1024eff124.h>
#elif defined(__32MZ1024EFF144__)
#  include <proc/p32mz1024eff144.h>
#elif defined(__32MZ1024EFG064__)
#  include <proc/p32mz1024efg064.h>
#elif defined(__32MZ1024EFG100__)
#  include <proc/p32mz1024efg100.h>
#elif defined(__32MZ1024EFG124__)
#  include <proc/p32mz1024efg124.h>
#elif defined(__32MZ1024EFG144__)
#  include <proc/p32mz1024efg144.h>
#elif defined(__32MZ1024EFH064__)
#  include <proc/p32mz1024efh064.h>
#elif defined(__32MZ1024EFH100__)
#  include <proc/p32mz1024efh100.h>
#elif defined(__32MZ1024EFH124__)
#  include <proc/p32mz1024efh124.h>
#elif defined(__32MZ1024EFH144__)
#  include <proc/p32mz1024efh144.h>
#elif defined(__32MZ1024EFK064__)
#  include <proc/p32mz1024efk064.h>
#elif defined(__32MZ1024EFK100__)
#  include <proc/p32mz1024efk100.h>
#elif defined(__32MZ1024EFK124__)
#  include <proc/p32mz1024efk124.h>
#elif defined(__32MZ1024EFK144__)
#  include <proc/p32mz1024efk144.h>
#elif defined(__32MZ1024EFM064__)
#  include <proc/p32mz1024efm064.h>
#elif defined(__32MZ1024EFM100__)
#  include <proc/p32mz1024efm100.h>
#elif defined(__32MZ1024EFM124__)
#  include <proc/p32mz1024efm124.h>
#elif defined(__32MZ1024EFM144__)
#  include <proc/p32mz1024efm144.h>
#elif defined(__32MZ2048ECG064__)
#  include <proc/p32mz2048ecg064.h>
#elif defined(__32MZ2048ECG100__)
#  include <proc/p32mz2048ecg100.h>
#elif defined(__32MZ2048ECG124__)
#  include <proc/p32mz2048ecg124.h>
#elif defined(__32MZ2048ECG144__)
#  include <proc/p32mz2048ecg144.h>
#elif defined(__32MZ2048ECH064__)
#  include <proc/p32mz2048ech064.h>
#elif defined(__32MZ2048ECH100__)
#  include <proc/p32mz2048ech100.h>
#elif defined(__32MZ2048ECH124__)
#  include <proc/p32mz2048ech124.h>
#elif defined(__32MZ2048ECH144__)
#  include <proc/p32mz2048ech144.h>
#elif defined(__32MZ2048ECM064__)
#  include <proc/p32mz2048ecm064.h>
#elif defined(__32MZ2048ECM100__)
#  include <proc/p32mz2048ecm100.h>
#elif defined(__32MZ2048ECM124__)
#  include <proc/p32mz2048ecm124.h>
#elif defined(__32MZ2048ECM144__)
#  include <proc/p32mz2048ecm144.h>
#elif defined(__32MZ2048EFG064__)
#  include <proc/p32mz2048efg064.h>
#elif defined(__32MZ2048EFG100__)
#  include <proc/p32mz2048efg100.h>
#elif defined(__32MZ2048EFG124__)
#  include <proc/p32mz2048efg124.h>
#elif defined(__32MZ2048EFG144__)
#  include <proc/p32mz2048efg144.h>
#elif defined(__32MZ2048EFH064__)
#  include <proc/p32mz2048efh064.h>
#elif defined(__32MZ2048EFH100__)
#  include <proc/p32mz2048efh100.h>
#elif defined(__32MZ2048EFH124__)
#  include <proc/p32mz2048efh124.h>
#elif defined(__32MZ2048EFH144__)
#  include <proc/p32mz2048efh144.h>
#elif defined(__32MZ2048EFM064__)
#  include <proc/p32mz2048efm064.h>
#elif defined(__32MZ2048EFM100__)
#  include <proc/p32mz2048efm100.h>
#elif defined(__32MZ2048EFM124__)
#  include <proc/p32mz2048efm124.h>
#elif defined(__32MZ2048EFM144__)
#  include <proc/p32mz2048efm144.h>
#elif defined(__32M4KCORE__)
#  include <proc/p32m4kcore.h>
#elif defined(__32MXGENERIC__)
#  include <proc/p32mxgeneric.h>
#else
#  error Unknown processor!
#endif

#include <xc.h>

#endif