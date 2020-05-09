#include <ultra64.h>
#include <global.h>

#define THIS ((ActorEnNnh*)thisx)

void EnNnh_Init(Actor *thisx, GlobalContext *ctxt) {
    ActorEnNnh* this = THIS;

    Actor_SetScale(thisx, 0.009999999776482582f);
    
    Collision_InitCylinderDefault(ctxt, &this->collision);
    Collision_InitCylinderWithData(ctxt, &this->collision, thisx, (ColCylinderInit *) &D_80C08A00); // D_80C08A00 => enNnhCylinderInit

    thisx->unk1F = (u8)1;
    thisx->topPosRot.pos = thisx->currPosRot.pos;
    thisx->topPosRot.pos.y += 30.0f;

    EnNnh_SetSubupdate1(thisx);
}


void EnNnh_Destroy(Actor *thisx, GlobalContext *ctxt) {
    ActorEnNnh* this = THIS;
    ColCylinder* collision = &this->collision;

    Collision_FiniCylinder(ctxt, collision);
}

void EnNnh_SetSubupdate1(Actor* thisx) {
    ActorEnNnh* this = THIS;
    this->update = (actor_func) &EnNnh_Subupdate1;
}

void EnNnh_Subupdate1(Actor* thisx, GlobalContext *ctxt) {
    GlobalContext *temp_a1;

    temp_a1 = ctxt;
    ctxt = ctxt;
    if (func_800B84D0(thisx, temp_a1) != 0) {
        func_801518B0(ctxt, 0x228U, thisx);
        EnNnh_SetSubupdate2(thisx);
        return;
    }
    func_800B8614(thisx, ctxt, 100.0f);
}

void EnNnh_SetSubupdate2(Actor* thisx) {
    ActorEnNnh* this = THIS;
    this->update = (actor_func) &EnNnh_Subupdate2;
}

void EnNnh_Subupdate2(Actor *thisx, GlobalContext *ctxt) {
    if (func_800B867C(thisx, ctxt) != 0) {
        EnNnh_SetSubupdate1(thisx);
    }
}

void EnNnh_Update(Actor *thisx, GlobalContext *ctxt) {    
    ActorEnNnh* this = THIS;
    ColCylinder* collision = &this->collision;

    this->update(thisx, ctxt);
    Collision_CylinderMoveToActor(thisx, collision);
    Collision_AddOT(ctxt, &ctxt->colCheckCtx, (ColCommon*) &this->collision);
}

GLOBAL_ASM("asm/non_matchings/z_en_nnh/EnNnh_Draw.asm")
// void EnNnh_Draw(Actor *thisx, GlobalContext *ctxt) {
//     GraphicsContext *sp24;
//     Gfx *sp1C;
//     Gfx *temp_v0;
//     Gfx *temp_v0_2;

//     sp24 = ctxt->state.gfxCtx;
//     func_8012C28C(ctxt->state.gfxCtx);
//     temp_v0 = sp24->polyOpa.p;
//     sp24->polyOpa.p = (Gfx *) (temp_v0 + 8);
//     temp_v0->words.w0 = 0xDA380003U;
//     sp24 = sp24;
//     sp1C = temp_v0;
//     sp1C->words.w1 = SysMatrix_AppendStateToPolyOpaDisp(ctxt->state.gfxCtx);
//     temp_v0_2 = sp24->polyOpa.p;
//     sp24->polyOpa.p = (Gfx *) (temp_v0_2 + 8);
//     temp_v0_2->words.w1 = (u32) (0x6000000 + 0x1510);
//     temp_v0_2->words.w0 = 0xDE000000U;
// }
