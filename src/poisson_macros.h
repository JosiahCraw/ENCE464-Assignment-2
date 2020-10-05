/*
`* Poisson Macros - A set of macros used for the
 * Jacobi Relaxation, These define the operation at
 * different boundary conditions, removing the requirements for if 
 * statements within the inner loops
 * 
 * Author: Jos Craw
 * Date: 4/10/2020
 */

/*
 * Macro for adding x + 1
 */
#define XUP res += input[((z * ysize) + y) * xsize + (x + 1)];

/*
 * Macro for adding x - 1
 */
#define XDOWN res += input[((z * ysize) + y) * xsize + (x - 1)];

/*
 * Macro for adding y + 1
 */
#define YUP res += input[((z * ysize) + (y + 1)) * xsize + x];

/*
 * Macro for adding y - 1
 */
#define YDOWN res += input[((z * ysize) + (y - 1)) * xsize + x];

/*
 * Macro for adding z + 1
 */
#define ZUP res += input[(((z + 1) * ysize) + y) * xsize + x];

/*
 * Macro for adding z - 1
 */
#define ZDOWN res += input[(((z - 1) * ysize) + y) * xsize + x];

/*
 * Macro for adding the previous source
 */
#define S_DELTA res -= delta * delta * source[((z * ysize) + y) * xsize + x];\

/*
 * Macro for saving the new potential
 */
#define S_POT potential[((z * ysize) + y) * xsize + x] = res;

/*
 * Macro for adding VBound
 */
#define VBOUND res += Vbound;

/*
 * Macro for preforming the division
 */
#define DIV res /= 6;

/*
 * Macro for setting res = 0
 */
#define CLR_RES res = 0;

/*
 * Macro for computing without boundary conditions
 */
#define COMPUTE \
        XUP\
        XDOWN\
        YUP\
        YDOWN\
        ZUP\
        ZDOWN\
        S_DELTA\
        DIV\
        S_POT

/*
 * Macro expansion for no boundary conditions
 */
#define XYZ \
		for (unsigned int z = 1; z < zsize-1; z++) {\
			for (unsigned int y = 1; y < ysize-1; y++) {\
				for (unsigned int x = 1; x < xsize-1; x++) {\
					double res = 0;\
					COMPUTE\
				}\
			}\
		}
		
/*
 * Macro expansion for no boundary conditions
 */
#define XYZ_N \
		for (unsigned int z = 1; z < zsize+1; z++) {\
			for (unsigned int y = 1; y < ysize-1; y++) {\
				for (unsigned int x = 1; x < xsize-1; x++) {\
					double res = 0;\
					COMPUTE\
				}\
			}\
		}

/*
 * Macro expansion for Z boundary conditions
 */
#define XY_Z \
        for (unsigned int y = 1; y < ysize-1; y++) {\
            for (unsigned int x = 1; x < xsize-1; x++) {\
                double res = 0;\
                \
                unsigned int z = 0;\
                XUP\
                XDOWN\
                YUP\
                YDOWN\
                ZUP\
                VBOUND /* ZDOWN */ \
                S_DELTA\
                DIV\
                S_POT\
                CLR_RES\
                \
                z = zsize - 1;\
                XUP\
                XDOWN\
                YUP\
                YDOWN\
                VBOUND /* ZUP */ \
                ZDOWN\
                S_DELTA\
                DIV\
                S_POT\
            }\
        }

/*
 * Macro expansion for Y boundary conditions
 */
#define X_YZ \
		for (unsigned int z = 1; z < zsize-1; z++) {\
            for (unsigned int x = 1; x < xsize-1; x++) {\
                double res = 0;\
                \
                unsigned int y = 0;\
                XUP\
                XDOWN\
                YUP\
                VBOUND /* YDOWN */ \
                ZUP\
                ZDOWN\
                S_DELTA\
                DIV\
                S_POT\
                CLR_RES\
                \
                y = ysize - 1;\
                XUP\
                XDOWN\
                VBOUND /* YUP */ \
                YDOWN\
                ZUP\
                ZDOWN\
                S_DELTA\
                DIV\
                S_POT\
            }\
        }

/*
 * Macro expansion for X boundary conditions
 */
#define _XYZ \
		for (unsigned int z = 1; z < zsize-1; z++) {\
            for (unsigned int y = 1; y < ysize-1; y++) {\
                double res = 0;\
                \
                unsigned int x = 0;\
                XUP\
                VBOUND /* XDOWN */ \
                YUP\
                YDOWN\
                ZUP\
                ZDOWN\
                S_DELTA\
                DIV\
                S_POT\
                CLR_RES\
                \
                x = zsize - 1;\
                VBOUND /* XUP */ \
                XDOWN\
                YUP\
                YDOWN\
                ZUP\
                ZDOWN\
                S_DELTA\
                DIV\
                S_POT\
            }\
        }

/*
 * Macro expansion for Y, Z boundary conditions
 */
#define X_Y_Z \
		for (unsigned int x = 1; x < xsize-1; x++) {\
            double res = 0;\
            unsigned int y = 0;\
            unsigned int z = 0;\
            \
            XUP\
            XDOWN\
            YUP\
            VBOUND /* YDOWN */ \
            ZUP\
            VBOUND /* ZDOWN */ \
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            y = ysize - 1;\
            z = 0;\
            \
            XUP\
            XDOWN\
            VBOUND /* YUP */ \
            YDOWN\
            ZUP\
            VBOUND /* ZDOWN */ \
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            y = 0;\
            z = zsize - 1;\
            \
            XUP\
            XDOWN\
            YUP\
            VBOUND /* YDOWN */ \
            VBOUND /* ZUP */ \
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            y = ysize - 1;\
            z = zsize - 1;\
            \
            XUP\
            XDOWN\
            VBOUND /* YUP */ \
            YDOWN\
            VBOUND /* ZUP */ \
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
        }


/*
 * Macro expansion for X, Z boundary conditions
 */
#define _XY_Z \
		for (unsigned int y = 1; y < ysize-1; y++) {\
            double res = 0;\
            \
            unsigned int x = 0;\
            unsigned int z = 0;\
            \
            XUP\
            VBOUND /* XDOWN */ \
            YUP\
            YDOWN\
            ZUP\
            VBOUND /* ZDOWN */ \
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = 0;\
            z = zsize - 1;\
            \
            XUP\
            VBOUND /* XDOWN */ \
            YUP\
            YDOWN\
            VBOUND /* ZUP */ \
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = xsize - 1;\
            z = 0;\
            \
            VBOUND /* XUP */ \
            XDOWN\
            YUP\
            YDOWN\
            ZUP\
            VBOUND /* ZDOWN */ \
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = xsize - 1;\
            z = zsize - 1;\
            \
            VBOUND /* XUP */ \
            XDOWN\
            YUP\
            YDOWN\
            VBOUND /* ZUP */ \
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
        }

/*
 * Macro expansion for X, Y boundary conditions
 */
#define _X_YZ \
		for (unsigned int z = 1; z < zsize-1; z++) {\
            double res = 0;\
            \
            unsigned int x = 0;\
            unsigned int y = 0;\
            \
            XUP\
            VBOUND /* XDOWN */ \
            YUP\
            VBOUND /* YDOWN */ \
            ZUP\
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = 0;\
            y = ysize - 1;\
            \
            XUP\
            VBOUND /* XDOWN */ \
            VBOUND /* YUP */ \
            YDOWN\
            ZUP\
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = xsize - 1;\
            y = 0;\
            \
            VBOUND /* XUP */ \
            XDOWN\
            YUP\
            VBOUND /* YDOWN */ \
            ZUP\
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
            CLR_RES\
            \
            x = xsize - 1;\
            y = ysize - 1;\
            \
            VBOUND /* XUP */ \
            XDOWN\
            VBOUND /* YUP */ \
            YDOWN\
            ZUP\
            ZDOWN\
            S_DELTA\
            DIV\
            S_POT\
        }

/*
 * Macro expansion for X, Y, Z boundary conditions
 */
#define _X_Y_Z \
        double res = 0;\
        \
        unsigned int x = 0;\
        unsigned int y = 0;\
        unsigned int z = 0;\
        \
        XUP\
        VBOUND /* XDOWN */\
        YUP\
        VBOUND /* YDOWN */ \
        ZUP\
        VBOUND /* ZDOWN */ \
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = 0;\
        y = 0;\
        z = zsize - 1;\
        \
        XUP\
        VBOUND /* XDOWN */ \
        YUP\
        VBOUND /* YDOWN */ \
        VBOUND /* ZUP */ \
        ZDOWN\
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = 0;\
        y = ysize - 1;\
        z = 0;\
        \
        XUP\
        VBOUND /* XDOWN */ \
        VBOUND /* YUP */ \
        YDOWN\
        ZUP\
        VBOUND /* ZDOWN */ \
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = 0;\
        y = ysize - 1;\
        z = zsize - 1;\
        \
        XUP\
        VBOUND /* XDOWN */ \
        VBOUND /* YUP */\
        YDOWN\
        VBOUND /* ZUP */ \
        ZDOWN\
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = xsize - 1;\
        y = 0;\
        z = 0;\
        \
        VBOUND /* XUP */ \
        XDOWN\
        YUP\
        VBOUND /* YDOWN */ \
        ZUP\
        VBOUND /* ZDOWN */ \
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = xsize - 1;\
        y = 0;\
        z = zsize - 1;\
        \
        VBOUND /* XUP */ \
        XDOWN\
        YUP\
        VBOUND /* YDOWN */ \
        VBOUND /* ZUP */ \
        ZDOWN\
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = xsize - 1;\
        y = ysize - 1;\
        z = 0;\
        \
        VBOUND /* XUP */ \
        XDOWN\
        VBOUND /* YUP */ \
        YDOWN\
        ZUP\
        VBOUND /* ZDOWN */ \
        S_DELTA\
        DIV\
        S_POT\
        CLR_RES\
        \
        x = xsize - 1;\
        y = ysize - 1;\
        z = zsize - 1;\
        \
        VBOUND /* XUP */ \
        XDOWN\
        VBOUND /* YUP */ \
        YDOWN\
        VBOUND /* ZUP */ \
        ZDOWN\
        S_DELTA\
        DIV\
        S_POT
    
